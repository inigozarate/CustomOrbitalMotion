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
    Foam::RBD::mjoints::mRs

Group
    grpRigidBodyDynamicsJoints

Description
    Spherical mjoint for rotation about the x/y/z-axes using a quaternion
    (Euler parameters) to avoid gimble-lock.

    Reference:
    \verbatim
        Featherstone, R. (2008).
        Rigid body dynamics algorithms.
        Springer.
        Chapter 4.
    \endverbatim

SourceFiles
    mRs.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_joints_Rs_H
#define RBD_joints_Rs_H

#include "mjoint.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mjoints
{

/*---------------------------------------------------------------------------*\
                         Class mRs Declaration
\*---------------------------------------------------------------------------*/

class mRs
:
    public mjoint
{

public:

    //- Runtime type information
    TypeName("mRs");


    // Constructors

        //- Construct for given model
        mRs();

        //- Construct for given model from dictionary
        mRs(const dictionary& dict);

        //- Clone this mjoint
        virtual autoPtr<mjoint> clone() const;


    //- Destructor
    virtual ~mRs();


    // Member Functions

        //- Return true as this mjoint describes rotation using a quaternion
        virtual bool unitQuaternion() const;

        //- Update the model state for this mjoint
        virtual void jcalc
        (
            mjoint::XSvc& J,
            const scalarField& q,
            const scalarField& qDot
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mjoints
} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
