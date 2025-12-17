/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
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

#include "mlinearSpring.H"
#include "mrigidBodyModel.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mrestraints
{
    defineTypeNameAndDebug(mlinearSpring, 0);

    addToRunTimeSelectionTable
    (
        mrestraint,
        mlinearSpring,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mrestraints::mlinearSpring::mlinearSpring
(
    const word& name,
    const dictionary& dict,
    const mrigidBodyModel& model
)
:
    mrestraint(name, dict, model)
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mrestraints::mlinearSpring::~mlinearSpring()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mrestraints::mlinearSpring::restrain
(
    scalarField& tau,
    Field<spatialVector>& fx,
    const mrigidBodyModelState& state
) const
{
    point attachmentPt = bodyPoint(refAttachmentPt_);

    // Current axis of the spring
    vector r = attachmentPt - anchor_;
    scalar magR = mag(r);
    r /= (magR + VSMALL);

    // Velocity of the attached end of the spring
    vector v = bodyPointVelocity(refAttachmentPt_).l();

    // Force and moment on the master body including optional damping
    vector force
    (
        (-stiffness_*(magR - restLength_) - damping_*(r & v))*r
    );

    vector moment(attachmentPt ^ force);

    if (model_.debug)
    {
        Info<< " attachmentPt " << attachmentPt
            << " attachmentPt - anchor " << r*magR
            << " spring length " << magR
            << " force " << force
            << " moment " << moment
            << endl;
    }

    // Accumulate the force for the restrained body
    fx[bodyIndex_] += spatialVector(moment, force);
}


bool Foam::RBD::mrestraints::mlinearSpring::read
(
    const dictionary& dict
)
{
    mrestraint::read(dict);

    coeffs_.readEntry("anchor", anchor_);
    coeffs_.readEntry("refAttachmentPt", refAttachmentPt_);
    coeffs_.readEntry("stiffness", stiffness_);
    coeffs_.readEntry("damping", damping_);
    coeffs_.readEntry("restLength", restLength_);

    return true;
}


void Foam::RBD::mrestraints::mlinearSpring::write
(
    Ostream& os
) const
{
    mrestraint::write(os);

    os.writeEntry("anchor", anchor_);
    os.writeEntry("refAttachmentPt", refAttachmentPt_);
    os.writeEntry("stiffness", stiffness_);
    os.writeEntry("damping", damping_);
    os.writeEntry("restLength", restLength_);
}


// ************************************************************************* //
