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
    Foam::mcompositeBody

Group
    grpRigidBodyDynamicsBodies

Description
    This specialized mrigidBody holds the original body after it has been merged
    into a parent.

SourceFiles
    mcompositeBodyI.H
    mcompositeBody.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_compositeBody_H
#define RBD_compositeBody_H

#include "mrigidBody.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{

/*---------------------------------------------------------------------------*\
                         Class mcompositeBody Declaration
\*---------------------------------------------------------------------------*/

class mcompositeBody
:
    public mrigidBody
{
    // Private data

        //- Original body from which this mcomposite-body was constructed
        autoPtr<mrigidBody> body_;

public:

    // Constructors

        //- Construct a merged version of the given mrigidBody
        //  providing the ID of the parent body to which this will be merged
        //  and the transform relative to the parent
        inline mcompositeBody(const autoPtr<mrigidBody>& bodyPtr);

        //- Return clone of this mcompositeBody
        virtual autoPtr<mrigidBody> clone() const;


    //- Destructor
    virtual ~mcompositeBody();


    // Member Functions

        //- Return the type name of the original body
        virtual const word& type() const;

        //- Return the original body from which this mcomposite-body
        //  was constructed
        inline const mrigidBody& body() const;

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mcompositeBodyI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
