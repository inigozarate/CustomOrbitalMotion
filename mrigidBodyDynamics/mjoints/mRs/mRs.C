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

#include "mRs.H"
#include "mrigidBodyModel.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mjoints
{
    defineTypeNameAndDebug(mRs, 0);

    addToRunTimeSelectionTable
    (
        mjoint,
        mRs,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mRs::mRs()
:
    mjoint(3)
{
    S_[0] = spatialVector(1, 0, 0, 0, 0, 0);
    S_[1] = spatialVector (0, 1, 0, 0, 0, 0);
    S_[2] = spatialVector(0, 0, 1, 0, 0, 0);
}


Foam::RBD::mjoints::mRs::mRs(const dictionary& dict)
:
    mjoint(3)
{
    S_[0] = spatialVector(1, 0, 0, 0, 0, 0);
    S_[1] = spatialVector (0, 1, 0, 0, 0, 0);
    S_[2] = spatialVector(0, 0, 1, 0, 0, 0);
}


Foam::autoPtr<Foam::RBD::mjoint> Foam::RBD::mjoints::mRs::clone() const
{
    return autoPtr<mjoint>(new mRs(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mRs::~mRs()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::RBD::mjoints::mRs::unitQuaternion() const
{
    return true;
}


void Foam::RBD::mjoints::mRs::jcalc
(
    mjoint::XSvc& J,
    const scalarField& q,
    const scalarField& qDot
) const
{
    J.X.E() = mjoint::unitQuaternion(q).R().T();
    J.X.r() = Zero;

    J.S = Zero;
    J.S.xx() = 1;
    J.S.yy() = 1;
    J.S.zz() = 1;

    J.v = spatialVector(qDot.block<vector>(qIndex_), Zero);
    J.c = Zero;
}


// ************************************************************************* //
