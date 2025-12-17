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

#include "mcompositeJoint.H"
#include "mrigidBodyModel.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mjoints
{
    defineTypeNameAndDebug(mcomposite, 0);

    addToRunTimeSelectionTable
    (
        mjoint,
        mcomposite,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Foam::RBD::mjoints::mcomposite::setLastJoint()
{
    last().mjoint::operator=(*this);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mcomposite::mcomposite(const PtrList<mjoint>& mjoints)
:
    PtrList<mjoint>(mjoints),
    mjoint(last())
{}


Foam::RBD::mjoints::mcomposite::mcomposite(const dictionary& dict)
:
    PtrList<mjoint>(dict.lookup("mjoints")),
    mjoint(last())
{}


Foam::autoPtr<Foam::RBD::mjoint> Foam::RBD::mjoints::mcomposite::clone() const
{
    return autoPtr<mjoint>(new mcomposite(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mjoints::mcomposite::~mcomposite()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mjoints::mcomposite::jcalc
(
    mjoint::XSvc& J,
    const scalarField& q,
    const scalarField& qDot
) const
{
    last().jcalc(J, q, qDot);
}


void Foam::RBD::mjoints::mcomposite::write(Ostream& os) const
{
    mjoint::write(os);
    os.writeKeyword("mjoints");
    os << static_cast<const PtrList<mjoint>&>(*this);
}


// ************************************************************************* //
