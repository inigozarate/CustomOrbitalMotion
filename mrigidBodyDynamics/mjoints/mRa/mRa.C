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

#include "mRa.H"
#include "mrigidBodyModel.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mjoints
{
    defineTypeNameAndDebug(mRa, 0);

    addToRunTimeSelectionTable
    (
        mjoint,
        mRa,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mRa::mRa(const vector& axis)
:
    mjoint(1)
{
    S_[0] = spatialVector(axis/mag(axis), Zero);
}


Foam::RBD::mjoints::mRa::mRa(const dictionary& dict)
:
    mRa(dict.get<vector>("axis"))
{}


Foam::autoPtr<Foam::RBD::mjoint> Foam::RBD::mjoints::mRa::clone() const
{
    return autoPtr<mjoint>(new mRa(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mRa::~mRa()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mjoints::mRa::jcalc
(
    mjoint::XSvc& J,
    const scalarField& q,
    const scalarField& qDot
) const
{
    J.X = Xr(S_[0].w(), q[qIndex_]);
    J.S1 = S_[0];
    J.v = S_[0]*qDot[qIndex_];
    J.c = Zero;
}


void Foam::RBD::mjoints::mRa::write(Ostream& os) const
{
    mjoint::write(os);
    os.writeEntry("axis", S_[0].w());
}


// ************************************************************************* //
