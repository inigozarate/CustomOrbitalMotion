/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
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

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const Foam::Time& Foam::RBD::mrigidBodyModel::time() const
{
    return time_;
}


inline Foam::label Foam::RBD::mrigidBodyModel::nBodies() const
{
    return bodies_.size();
}


inline Foam::PtrList<Foam::RBD::mrigidBody>
Foam::RBD::mrigidBodyModel::mbodies() const
{
    return bodies_;
}


inline const Foam::DynamicList<Foam::label>&
Foam::RBD::mrigidBodyModel::lambda() const
{
    return lambda_;
}


inline const Foam::PtrList<Foam::RBD::mjoint>&
Foam::RBD::mrigidBodyModel::mjoints() const
{
    return joints_;
}


inline Foam::label Foam::RBD::mrigidBodyModel::nDoF() const
{
    return nDoF_;
}


inline bool Foam::RBD::mrigidBodyModel::unitQuaternions() const
{
    return unitQuaternions_;
}


inline const Foam::vector& Foam::RBD::mrigidBodyModel::g() const
{
    return g_;
}


inline Foam::vector& Foam::RBD::mrigidBodyModel::g()
{
    return g_;
}


inline const Foam::word& Foam::RBD::mrigidBodyModel::name
(
    const label bodyID
) const
{
    if (merged(bodyID))
    {
        return mergedBody(bodyID).name();
    }
    else
    {
        return bodies_[bodyID].name();
    }
}


inline const Foam::RBD::mrigidBodyInertia&
Foam::RBD::mrigidBodyModel::I(const label i) const
{
    return bodies_[i];
}


inline const Foam::spatialVector&
Foam::RBD::mrigidBodyModel::v(const label i) const
{
    return v_[i];
}

inline const Foam::spatialVector&
Foam::RBD::mrigidBodyModel::a(const label i) const
{
    return a_[i];
}

inline bool Foam::RBD::mrigidBodyModel::merged(label bodyID) const
{
    return bodyID < 0;
}


inline Foam::label Foam::RBD::mrigidBodyModel::master(label bodyID) const
{
    if (bodyID < 0)
    {
        return mergedBody(bodyID).masterID();
    }
    else
    {
        return bodyID;
    }
}


inline Foam::label
Foam::RBD::mrigidBodyModel::mergedBodyID(const label mergedBodyIndex) const
{
    return -1 - mergedBodyIndex;
}


inline Foam::label
Foam::RBD::mrigidBodyModel::mergedBodyIndex(const label mergedBodyID) const
{
    return -1 - mergedBodyID;
}


inline const Foam::RBD::msubBody&
Foam::RBD::mrigidBodyModel::mergedBody(label mergedBodyID) const
{
    if (!merged(mergedBodyID))
    {
        FatalErrorInFunction
            << "Body " << mergedBodyID << " has not been merged"
            << abort(FatalError);
    }

    return mergedBodies_[mergedBodyIndex(mergedBodyID)];
}


inline Foam::label Foam::RBD::mrigidBodyModel::bodyID(const word& name) const
{
    return bodyIDs_[name];
}


inline Foam::vector Foam::RBD::mrigidBodyModel::masterPoint
(
    const label bodyID,
    const vector& p
) const
{
    if (merged(bodyID))
    {
        return
        (
            mergedBody(bodyID).masterXT().inv()
         && spatialVector(Zero, p)
        ).l();
    }
    else
    {
        return p;
    }
}


inline Foam::spatialVector Foam::RBD::mrigidBodyModel::v
(
    const label bodyID,
    const vector& p
) const
{
    return
    (
        spatialTransform
        (
            X0_[master(bodyID)].E().T(),
            masterPoint(bodyID, p)
        )
      & v_[master(bodyID)]
    );
}


// ************************************************************************* //
