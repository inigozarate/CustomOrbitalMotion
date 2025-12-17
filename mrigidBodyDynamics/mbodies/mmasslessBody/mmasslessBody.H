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
    Foam::mmasslessBody

Group
    grpRigidBodyDynamicsBodies

Description

SourceFiles
    masslessBodyI.H
    mmasslessBody.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_mmasslessBody_H
#define RBD_mmasslessBody_H

#include "mrigidBody.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{

/*---------------------------------------------------------------------------*\
                         Class mmasslessBody Declaration
\*---------------------------------------------------------------------------*/

class mmasslessBody
:
    public mrigidBody
{

public:

    //- Runtime type information
    TypeName("mmasslessBody");


    // Constructors

        //- Construct a massless body
        inline mmasslessBody();

        //- Construct a named massless body
        inline mmasslessBody(const word& name);

        //- Construct from dictionary
        inline mmasslessBody
        (
            const word& name,
            const dictionary& dict
        );

        //- Return clone of this mmasslessBody
        virtual autoPtr<mrigidBody> clone() const;


    //- Destructor
    virtual ~mmasslessBody();


    // Member Functions

        //- Return true if this body is a massless component of a composite body
        virtual bool mmassless() const;

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mmasslessBodyI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
