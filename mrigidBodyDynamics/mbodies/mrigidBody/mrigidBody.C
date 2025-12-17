/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
    Copyright (C) 2019-2021 OpenCFD Ltd.
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

#include "mrigidBody.H"
#include "msubBody.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
    defineTypeNameAndDebug(mrigidBody, 0);
    defineRunTimeSelectionTable(mrigidBody, dictionary);

    addToRunTimeSelectionTable
    (
        mrigidBody,
        mrigidBody,
        dictionary
    );
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::RBD::mrigidBody> Foam::RBD::mrigidBody::clone() const
{
    return autoPtr<mrigidBody>::New(*this);
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::RBD::mrigidBody> Foam::RBD::mrigidBody::New
(
    const word& name,
    const scalar& m,
    const vector& c,
    const symmTensor& Ic
)
{
    return autoPtr<mrigidBody>::New(name, m, c, Ic);
}


Foam::autoPtr<Foam::RBD::mrigidBody> Foam::RBD::mrigidBody::New
(
    const word& name,
    const dictionary& dict
)
{
    const word bodyType(dict.get<word>("type"));

    auto* ctorPtr = dictionaryConstructorTable(bodyType);

    if (!ctorPtr)
    {
        FatalIOErrorInLookup
        (
            dict,
            "mrigidBody",
            bodyType,
            *dictionaryConstructorTablePtr_
        ) << exit(FatalIOError);
    }

    return autoPtr<mrigidBody>(ctorPtr(name, dict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mrigidBody::~mrigidBody()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::RBD::mrigidBody::massless() const
{
    return false;
}


void Foam::RBD::mrigidBody::merge(const msubBody& msubBody)
{
    *this = mrigidBody
    (
        name(),
        *this + transform(msubBody.masterXT(), msubBody.body())
    );
}


void Foam::RBD::mrigidBody::write(Ostream& os) const
{
    os.writeEntry("type", type());
    os.writeEntry("mass", m());
    os.writeEntry("centreOfMass", c());
    os.writeEntry("inertia", Ic());
}


// ************************************************************************* //
