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

#include "mPxyz.H"
#include "mrigidBodyModel.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mjoints
{
    defineTypeNameAndDebug(mPxyz, 0);

    addToRunTimeSelectionTable
    (
        mjoint,
        mPxyz,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mPxyz::mPxyz()
:
    mjoint(3)
{
    S_[0] = spatialVector(0, 0, 0, 1, 0, 0);
    S_[1] = spatialVector(0, 0, 0, 0, 1, 0);
    S_[2] = spatialVector(0, 0, 0, 0, 0, 1);
}


Foam::RBD::mjoints::mPxyz::mPxyz(const dictionary& dict)
:
    mjoint(3)
{
    S_[0] = spatialVector(0, 0, 0, 1, 0, 0);
    S_[1] = spatialVector(0, 0, 0, 0, 1, 0);
    S_[2] = spatialVector(0, 0, 0, 0, 0, 1);
}


Foam::autoPtr<Foam::RBD::mjoint> Foam::RBD::mjoints::mPxyz::clone() const
{
    return autoPtr<mjoint>(new mPxyz(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mPxyz::~mPxyz()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mjoints::mPxyz::jcalc
(
    mjoint::XSvc& J,
    const scalarField& q,
    const scalarField& qDot
) const
{
    J.X.E() = tensor::I;
    J.X.r() = q.block<vector>(qIndex_);

    J.S = Zero;
    J.S(3,0) = 1;
    J.S(4,1) = 1;
    J.S(5,2) = 1;

    J.v = spatialVector(Zero, qDot.block<vector>(qIndex_));
    J.c = Zero;
}


// ************************************************************************* //
