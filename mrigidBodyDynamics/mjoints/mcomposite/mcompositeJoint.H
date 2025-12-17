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
    Foam::RBD::mjoints::mcomposite

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
    mcomposite.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_joints_composite_H
#define RBD_joints_composite_H

#include "mjoint.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{

// Forward declaration of classes
class mrigidBodyModel;

namespace mjoints
{

/*---------------------------------------------------------------------------*\
                         Class mcomposite Declaration
\*---------------------------------------------------------------------------*/

class mcomposite
:
    public PtrList<mjoint>,
    public mjoint
{
    // Private member functions

        //- Set the properties of the last mjoint following construction
        //  of the body containing the mjoint
        void setLastJoint();


public:

    //- Runtime type information
    TypeName("mcomposite");

    //- Allow the mrigidBodyModel class to set the last mjoint state
    friend class Foam::RBD::mrigidBodyModel;


    // Constructors

        //- Construct for given PtrList<mjoint>
        mcomposite(const PtrList<mjoint>& mjoints);

        //- Construct for given model from dictionary
        mcomposite(const dictionary& dict);

        //- Clone this mjoint
        virtual autoPtr<mjoint> clone() const;


    //- Destructor
    virtual ~mcomposite();


    // Member Functions

        //- Update the model state for this mjoint
        virtual void jcalc
        (
            mjoint::XSvc& J,
            const scalarField& q,
            const scalarField& qDot
        ) const;

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
