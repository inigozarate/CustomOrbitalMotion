/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2017 OpenFOAM Foundation
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

#include "mlinearDamper.H"
#include "mrigidBodyModel.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mrestraints
{
    defineTypeNameAndDebug(mlinearDamper, 0);

    addToRunTimeSelectionTable
    (
        mrestraint,
        mlinearDamper,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mrestraints::mlinearDamper::mlinearDamper
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

Foam::RBD::mrestraints::mlinearDamper::~mlinearDamper()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mrestraints::mlinearDamper::restrain
(
    scalarField& tau,
    Field<spatialVector>& fx,
    const mrigidBodyModelState& state
) const
{
    vector force = -coeff_*model_.v(model_.master(bodyID_)).l();

    if (model_.debug)
    {
        Info<< " force " << force << endl;
    }

    // Accumulate the force for the restrained body
    fx[bodyIndex_] += model_.X0(bodyID_).T() & spatialVector(Zero, force);
}


bool Foam::RBD::mrestraints::mlinearDamper::read
(
    const dictionary& dict
)
{
    mrestraint::read(dict);

    coeffs_.readEntry("coeff", coeff_);

    return true;
}


void Foam::RBD::mrestraints::mlinearDamper::write
(
    Ostream& os
) const
{
    mrestraint::write(os);

    os.writeEntry("coeff", coeff_);
}


// ************************************************************************* //
