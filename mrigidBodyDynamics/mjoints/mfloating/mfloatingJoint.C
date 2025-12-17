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

#include "mfloatingJoint.H"
#include "mrigidBodyModel.H"
#include "addToRunTimeSelectionTable.H"

#include "mRs.H"
#include "mRzyx.H"
#include "mPxyz.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mjoints
{
    defineTypeNameAndDebug(mfloating, 0);

    addToRunTimeSelectionTable
    (
        mjoint,
        mfloating,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

Foam::RBD::mjoints::mcomposite Foam::RBD::mjoints::mfloating::sixDoF()
{
    PtrList<mjoint> cj(2);
    cj.set(0, new mjoints::mPxyz());

    // The quaternion-based spherical mjoint could be used
    // but then w must be set appropriately
    //cj.set(1, new mjoints::mRs());

    // Alternatively the Euler-angle mjoint can be used
    cj.set(1, new mjoints::mRzyx());

    return mcomposite(cj);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mfloating::mfloating()
:
    mcomposite(sixDoF())
{}


Foam::RBD::mjoints::mfloating::mfloating(const dictionary& dict)
:
    mfloating()
{}


Foam::autoPtr<Foam::RBD::mjoint> Foam::RBD::mjoints::mfloating::clone() const
{
    return autoPtr<mjoint>(new mfloating(*this));
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mjoints::mfloating::write(Ostream& os) const
{
    mjoint::write(os);
}


// ************************************************************************* //
