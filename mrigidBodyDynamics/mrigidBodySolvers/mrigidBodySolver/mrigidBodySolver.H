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
    Foam::RBD::mrigidBodySolver

Description

SourceFiles
    mrigidBodySolver.C
    newSixDoFSolver.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_rigidBodySolver_H
#define RBD_rigidBodySolver_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mrigidBodyMotion.H"
#include "runTimeSelectionTables.H"

namespace Foam
{
namespace RBD
{

/*---------------------------------------------------------------------------*\
                         Class mrigidBodySolver Declaration
\*---------------------------------------------------------------------------*/

class mrigidBodySolver
{
protected:

    // Protected data

        //- The rigid-body model
        mrigidBodyMotion& model_;


        //- Return the motion state
        inline mrigidBodyModelState& state();

        //- Return the current mjoint position and orientation
        inline scalarField& q();

        //- Return the current mjoint quaternion

        //- Return the current mjoint velocity
        inline scalarField& qDot();

        //- Return the current mjoint acceleration
        inline scalarField& qDdot();

        //- Return the current time-step
        inline scalar deltaT() const;


        //- Return the previous motion state
        inline const mrigidBodyModelState& state0() const;

        //- Return the current mjoint position and orientation
        inline const scalarField& q0() const;

        //- Return the current mjoint quaternion

        //- Return the current mjoint velocity
        inline const scalarField& qDot0() const;

        //- Return the current mjoint acceleration
        inline const scalarField& qDdot0() const;

        //- Return the previous time-step
        inline scalar deltaT0() const;

        //- Correct the quaternion mjoints based on the current change in q
        void correctQuaternionJoints();


public:

    //- Runtime type information
    TypeName("mrigidBodySolver");


    // Declare runtime construction

        declareRunTimeSelectionTable
        (
            autoPtr,
            mrigidBodySolver,
            dictionary,
            (
                mrigidBodyMotion& body,
                const dictionary& dict
            ),
            (body, dict)
        );


    // Constructors

        // Construct for given body
        mrigidBodySolver(mrigidBodyMotion& body);


    //- Destructor
    virtual ~mrigidBodySolver();


    // Selectors

        static autoPtr<mrigidBodySolver> New
        (
            mrigidBodyMotion& body,
            const dictionary& dict
        );


    // Member Functions

        //- Integrate the rigid-body motion for one time-step
        virtual void solve
        (
            const scalarField& tau,
            const Field<spatialVector>& fx
        ) = 0;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mrigidBodySolverI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
