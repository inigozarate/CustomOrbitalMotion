/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019 OpenFOAM Foundation
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

#include "mexternalForce.H"
#include "mrigidBodyModel.H"
#include "mrigidBodyModelState.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mrestraints
{
    defineTypeNameAndDebug(mexternalForce, 0);

    addToRunTimeSelectionTable
    (
        mrestraint,
        mexternalForce,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mrestraints::mexternalForce::mexternalForce
(
    const word& name,
    const dictionary& dict,
    const mrigidBodyModel& model
)
:
    mrestraint(name, dict, model),
    externalForce_(nullptr),
    location_(Zero)
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mrestraints::mexternalForce::~mexternalForce()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mrestraints::mexternalForce::restrain
(
    scalarField& tau,
    Field<spatialVector>& fx,
    const mrigidBodyModelState& state
) const
{
    const vector force = externalForce_().value(state.t());
    const vector moment(location_ ^ force);

    if (model_.debug)
    {
        Info<< " location " << location_
            << " force " << force
            << " moment " << moment
            << endl;
    }

    // Accumulate the force for the restrained body
    fx[bodyIndex_] += spatialVector(moment, force);
}


bool Foam::RBD::mrestraints::mexternalForce::read
(
    const dictionary& dict
)
{
    mrestraint::read(dict);

    coeffs_.readEntry("location", location_);

    externalForce_ = Function1<vector>::New("force", coeffs_);

    return true;
}


void Foam::RBD::mrestraints::mexternalForce::write
(
    Ostream& os
) const
{
    mrestraint::write(os);

    os.writeEntry("location", location_);

    externalForce_().writeData(os);
}


// ************************************************************************* //
