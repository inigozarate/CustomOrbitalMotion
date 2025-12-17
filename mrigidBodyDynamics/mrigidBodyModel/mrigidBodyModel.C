/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "mrigidBodyModel.H"
#include "mmasslessBody.H"
#include "mcompositeBody.H"
#include "mjointBody.H"
#include "mnullJoint.H"
#include "mrigidBodyRestraint.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
    defineTypeNameAndDebug(mrigidBodyModel, 0);
}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::RBD::mrigidBodyModel::initializeRootBody()
{
    bodies_.append(new mmasslessBody("root"));
    lambda_.append(0);
    bodyIDs_.insert("root", 0);
    joints_.append(new mjoints::mnull());
    XT_.append(spatialTransform());

    nDoF_ = 0;
    unitQuaternions_ = false;

    resizeState();
}


void Foam::RBD::mrigidBodyModel::resizeState()
{
    Xlambda_.append(spatialTransform());
    X0_.append(spatialTransform());

    v_.append(Zero);
    a_.append(Zero);
    c_.append(Zero);

    IA_.append(spatialTensor::I);
    pA_.append(Zero);

    S_.append(Zero);
    S1_.append(Zero);
    U_.append(Zero);
    U1_.append(Zero);
    Dinv_.append(Zero);
    u_.append(Zero);
}


void Foam::RBD::mrigidBodyModel::addRestraints
(
    const dictionary& dict
)
{
    if (dict.found("mrestraints"))
    {
        const dictionary& restraintDict = dict.subDict("mrestraints");

        label i = 0;

        restraints_.setSize(restraintDict.size());

        for (const entry& dEntry : restraintDict)
        {
            if (dEntry.isDict())
            {
                restraints_.set
                (
                    i++,
                    mrestraint::New
                    (
                        dEntry.keyword(),
                        dEntry.dict(),
                        *this
                    )
                );
            }
        }

        restraints_.setSize(i);
    }
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Foam::label Foam::RBD::mrigidBodyModel::join_
(
    const label parentID,
    const spatialTransform& XT,
    autoPtr<mjoint> jointPtr,
    autoPtr<mrigidBody> bodyPtr
)
{
    // Append the body
    const mrigidBody& body = bodyPtr();
    bodies_.append(bodyPtr);
    const label bodyID = nBodies()-1;
    bodyIDs_.insert(body.name(), bodyID);

    // If the parentID refers to a merged body find the parent into which it has
    // been merged and set lambda and XT accordingly
    if (merged(parentID))
    {
        const msubBody& sBody = mergedBody(parentID);
        lambda_.append(sBody.masterID());
        XT_.append(XT & sBody.masterXT());
    }
    else
    {
        lambda_.append(parentID);
        XT_.append(XT);
    }

    // Append the mjoint
    const mjoint& prevJoint = joints_[joints_.size() - 1];
    joints_.append(jointPtr);
    mjoint& curJoint = joints_[joints_.size() - 1];
    curJoint.index() = joints_.size() - 1;
    curJoint.qIndex() = prevJoint.qIndex() + prevJoint.nDoF();

    // Increment the degrees of freedom
    nDoF_ += curJoint.nDoF();
    unitQuaternions_ = unitQuaternions_ || curJoint.unitQuaternion();

    resizeState();

    return bodyID;
}


// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * * //

Foam::RBD::mrigidBodyModel::mrigidBodyModel(const Time& time)
:
    time_(time),
    g_(Zero)
{
    initializeRootBody();
}


Foam::RBD::mrigidBodyModel::mrigidBodyModel
(
    const Time& time,
    const dictionary& dict
)
:
    time_(time),
    g_(Zero)
{
    initializeRootBody();

    const dictionary& bodiesDict = dict.subDict("mbodies");

    for (const entry& dEntry : bodiesDict)
    {
        const keyType& key = dEntry.keyword();
        const dictionary& bodyDict = dEntry.dict();

        if (bodyDict.found("mergeWith"))
        {
            merge
            (
                bodyID(bodyDict.get<word>("mergeWith")),
                bodyDict.get<spatialTransform>("transform"),
                mrigidBody::New(key, bodyDict)
            );
        }
        else
        {
            join
            (
                bodyID(bodyDict.get<word>("parent")),
                bodyDict.get<spatialTransform>("transform"),
                mjoint::New(bodyDict.subDict("mjoint")),
                mrigidBody::New(key, bodyDict)
            );
        }
    }

    // Read the mrestraints and any other re-readable settings.
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mrigidBodyModel::~mrigidBodyModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::label Foam::RBD::mrigidBodyModel::join
(
    const label parentID,
    const spatialTransform& XT,
    autoPtr<mjoint> jointPtr,
    autoPtr<mrigidBody> bodyPtr
)
{
    if (isA<mjoints::mcomposite>(jointPtr()))
    {
        return join
        (
            parentID,
            XT,
            autoPtr<mjoints::mcomposite>
            (
                dynamic_cast<mjoints::mcomposite*>(jointPtr.ptr())
            ),
            bodyPtr
        );
    }
    else
    {
        return join_
        (
            parentID,
            XT,
            jointPtr,
            bodyPtr
        );
    }
}


Foam::label Foam::RBD::mrigidBodyModel::join
(
    const label parentID,
    const spatialTransform& XT,
    autoPtr<mjoints::mcomposite> cJointPtr,
    autoPtr<mrigidBody> bodyPtr
)
{
    label parent = parentID;
    mjoints::mcomposite& cJoint = cJointPtr();

    // For all but the final mjoint in the set add a mjointBody with the
    // mjoint and transform
    for (label j=0; j<cJoint.size()-1; j++)
    {
        parent = join_
        (
            parent,
            j == 0 ? XT : spatialTransform(),
            cJoint[j].clone(),
            autoPtr<mrigidBody>(new mjointBody)
        );
    }

    // For the final mjoint in the set add the real body
    parent = join_
    (
        parent,
        cJoint.size() == 1 ? XT : spatialTransform(),
        autoPtr<mjoint>(cJointPtr.ptr()),
        bodyPtr
    );

    // Set the properties of the last mjoint in the list to those set
    // by mrigidBodyModel
    cJoint.setLastJoint();

    return parent;
}


void Foam::RBD::mrigidBodyModel::makeComposite(const label bodyID)
{
    if (!isA<mcompositeBody>(bodies_[bodyID]))
    {
        // Retrieve the un-merged body
        autoPtr<mrigidBody> bodyPtr = bodies_.release(bodyID);

        // Insert the mcompositeBody containing the original body
        bodies_.set
        (
            bodyID,
            new mcompositeBody(bodyPtr)
        );
    }
}


Foam::label Foam::RBD::mrigidBodyModel::merge
(
    const label parentID,
    const spatialTransform& XT,
    autoPtr<mrigidBody> bodyPtr
)
{
    autoPtr<msubBody> sBodyPtr;

    // If the parentID refers to a merged body find the parent into which it has
    // been merged and merge this on into the same parent with the appropriate
    // transform
    if (merged(parentID))
    {
        const msubBody& sBody = mergedBody(parentID);

        makeComposite(sBody.masterID());

        sBodyPtr.reset
        (
            new msubBody
            (
                bodyPtr,
                bodies_[sBody.masterID()].name(),
                sBody.masterID(),
                XT & sBody.masterXT()
            )
        );
    }
    else
    {
        makeComposite(parentID);

        sBodyPtr.reset
        (
            new msubBody
            (
                bodyPtr,
                bodies_[parentID].name(),
                parentID,
                XT
            )
        );
    }

    const msubBody& sBody = sBodyPtr();
    mergedBodies_.append(sBodyPtr);

    // Merge the sub-body with the parent
    bodies_[sBody.masterID()].merge(sBody);

    const label sBodyID = mergedBodyID(mergedBodies_.size() - 1);
    bodyIDs_.insert(sBody.name(), sBodyID);

    return sBodyID;
}


Foam::spatialTransform Foam::RBD::mrigidBodyModel::X0
(
    const label bodyId
) const
{
    if (merged(bodyId))
    {
        const msubBody& mBody = mergedBody(bodyId);
        return mBody.masterXT() & X0_[mBody.masterID()];
    }

    return X0_[bodyId];
}


void Foam::RBD::mrigidBodyModel::write(Ostream& os) const
{
    os.beginBlock("mbodies");

    // Write the moving mbodies
    for (label i=1; i<nBodies(); i++)
    {
        // Do not write mjoint-mbodies created automatically to support elements
        // of mcomposite mjoints
        if (!isType<mjointBody>(bodies_[i]))
        {
            os.beginBlock(bodies_[i].name());

            bodies_[i].write(os);

            os.writeEntry("parent", bodies_[lambda_[i]].name());
            os.writeEntry("transform", XT_[i]);

            os  << indent << "mjoint" << nl
                << joints_[i] << endl;

            os.endBlock();
        }
    }

    // Write the mbodies merged into the parent mbodies for efficiency
    forAll(mergedBodies_, i)
    {
        os.beginBlock(mergedBodies_[i].name());

        mergedBodies_[i].body().write(os);

        os.writeEntry("transform", mergedBodies_[i].masterXT());
        os.writeEntry("mergeWith", mergedBodies_[i].masterName());

        os.endBlock();
    }

    os.endBlock();


    if (!restraints_.empty())
    {
        os.beginBlock("mrestraints");

        forAll(restraints_, ri)
        {
            // const word& restraintType(restraints_[ri].type());

            os.beginBlock(restraints_[ri].name());

            restraints_[ri].write(os);

            os.endBlock();
        }

        os.endBlock();
    }
}


bool Foam::RBD::mrigidBodyModel::read(const dictionary& dict)
{
    restraints_.clear();
    addRestraints(dict);

    return true;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

Foam::Ostream& Foam::RBD::operator<<(Ostream& os, const mrigidBodyModel& rbm)
{
    rbm.write(os);
    return os;
}


// ************************************************************************* //
