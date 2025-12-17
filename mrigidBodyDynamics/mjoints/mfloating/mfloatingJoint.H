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
    Foam::RBD::mjoints::mfloating

Group
    grpRigidBodyDynamicsJoints

Description
    Prismatic mjoint for translation along the specified arbitrary axis.

    Reference:
    \verbatim
        Featherstone, R. (2008).
        Rigid body dynamics algorithms.
        Springer.
        Chapter 4.
    \endverbatim

SourceFiles
    mfloating.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_joints_floating_H
#define RBD_joints_floating_H

#include "mcompositeJoint.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mjoints
{

/*---------------------------------------------------------------------------*\
                         Class mfloating Declaration
\*---------------------------------------------------------------------------*/

class mfloating
:
    public mcomposite
{
    // Private member functions

        //- Return a list of mjoints needed to emulate a mfloating body
        static mcomposite sixDoF();


public:

    //- Runtime type information
    TypeName("mfloating");


    // Constructors

        //- Construct
        mfloating();

        //- Construct for given model from dictionary
        mfloating(const dictionary& dict);

        //- Clone this mjoint
        virtual autoPtr<mjoint> clone() const;


    //- Destructor
    virtual ~mfloating() = default;


    // Member Functions

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mjoints
} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
