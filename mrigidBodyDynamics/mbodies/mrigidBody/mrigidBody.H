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

Class
    Foam::RBD::mrigidBody

Group
    grpRigidBodyDynamicsBodies

Description

SourceFiles
    mrigidBodyI.H

\*---------------------------------------------------------------------------*/

#ifndef RBD_rigidBody_H
#define RBD_rigidBody_H

#include "mrigidBodyInertia.H"
#include "dictionary.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{

// Forward declaration of classes
class msubBody;

// Forward declaration of friend functions and operators
class mrigidBody;

inline Ostream& operator<<(Ostream&, const mrigidBody&);


/*---------------------------------------------------------------------------*\
                         Class mrigidBody Declaration
\*---------------------------------------------------------------------------*/

class mrigidBody
:
    public mrigidBodyInertia
{
    // Private data

        //- Name of body
        word name_;


public:

    //- Runtime type information
    TypeName("mrigidBody");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            mrigidBody,
            dictionary,
            (const word& name, const dictionary& dict),
            (name, dict)
        );


    // Constructors

        //- Construct from mass, centre of mass and moment of inertia tensor
        //  about the centre of mass
        inline mrigidBody
        (
            const word& name,
            const scalar& m,
            const vector& c,
            const symmTensor& Ic
        );

        //- Construct from with the given mrigidBodyInertia
        inline mrigidBody
        (
            const word& name,
            const mrigidBodyInertia& rbi
        );

        //- Construct from dictionary
        inline mrigidBody
        (
            const word& name,
            const dictionary& dict
        );

        //- Return clone of this mrigidBody
        virtual autoPtr<mrigidBody> clone() const;


    // Selectors

        //- Select constructed from components
        static autoPtr<mrigidBody> New
        (
            const word& name,
            const scalar& m,
            const vector& c,
            const symmTensor& Ic
        );

        //- Select constructed from name and dictionary
        static autoPtr<mrigidBody> New
        (
            const word& name,
            const dictionary& dict
        );


    //- Destructor
    virtual ~mrigidBody();


    // Member Functions

        //- Return name
        inline const word& name() const;

        //- Return false as this body is not massless
        virtual bool massless() const;

        //- Merge a body into this parent body
        void merge(const msubBody&);

        //- Write
        virtual void write(Ostream&) const;


    // Ostream Operator

        friend Ostream& operator<<(Ostream&, const mrigidBody&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mrigidBodyI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
