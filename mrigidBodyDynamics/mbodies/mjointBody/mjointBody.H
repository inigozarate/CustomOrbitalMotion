/*---------------------------------------------------------------------------*\3
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

Class
    Foam::mjointBody

Group
    grpRigidBodyDynamicsBodies

Description

SourceFiles
    mjointBodyI.H
    mjointBody.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_jointBody_H
#define RBD_jointBody_H

#include "mmasslessBody.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{

/*---------------------------------------------------------------------------*\
                         Class mjointBody Declaration
\*---------------------------------------------------------------------------*/

class mjointBody
:
    public mmasslessBody
{

public:

    //- Runtime type information
    TypeName("mjointBody");


    // Constructors

        //- Construct a mjoint body
        inline mjointBody();

        //- Construct a named mjoint body
        inline mjointBody(const word& name);

        //- Construct from dictionary
        inline mjointBody
        (
            const word& name,
            const dictionary& dict
        );

        //- Return clone of this mjointBody
        virtual autoPtr<mrigidBody> clone() const;


    //- Destructor
    virtual ~mjointBody();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mjointBodyI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
