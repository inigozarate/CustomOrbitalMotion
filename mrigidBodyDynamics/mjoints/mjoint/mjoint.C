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

#include "mjoint.H"
#include "mrigidBodyModel.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
    defineTypeNameAndDebug(mjoint, 0);
    defineRunTimeSelectionTable(mjoint, dictionary);
}
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::RBD::mjoint> Foam::RBD::mjoint::New(mjoint* jointPtr)
{
    return autoPtr<mjoint>(jointPtr);
}


Foam::autoPtr<Foam::RBD::mjoint> Foam::RBD::mjoint::New
(
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
            "mjoint",
            bodyType,
            *dictionaryConstructorTablePtr_
        ) << exit(FatalIOError);
    }

    return autoPtr<mjoint>(ctorPtr(dict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mjoint::~mjoint()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mjoint::write(Ostream& os) const
{
    os.writeEntry("type", type());
}


// ************************************************************************* //
