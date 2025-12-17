/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019 OpenFOAM Foundation
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
    Foam::RBD::mrestraints::mexternalForce

Group
    grpRigidBodyDynamicsRestraints

Description
    Time-dependent external force mrestraint using Function1.

Usage
    Example applying a constant force to the floatingObject:
    \verbatim
    mrestraints
    {
        force
        {
            type        mexternalForce;
            body        floatingObject;
            location    (0 0 0);
            force       (100 0 0);
        }
    }
    \endverbatim

SourceFiles
    mexternalForce.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_restraints_externalForce_H
#define RBD_restraints_externalForce_H

#include "mrigidBodyRestraint.H"
#include "Function1.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mrestraints
{

/*---------------------------------------------------------------------------*\
                          Class mexternalForce Declaration
\*---------------------------------------------------------------------------*/

class mexternalForce
:
    public mrestraint
{
    // Private data

        //- External force (N)
        autoPtr<Function1<vector>> externalForce_;

        //- Point of application of the force
        vector location_;


public:

    //- Runtime type information
    TypeName("mexternalForce");


    // Constructors

        //- Construct from components
        mexternalForce
        (
            const word& name,
            const dictionary& dict,
            const mrigidBodyModel& model
        );

        //- Construct and return a clone
        virtual autoPtr<mrestraint> clone() const
        {
            return autoPtr<mrestraint>
            (
                new mexternalForce(*this)
            );
        }


    //- Destructor
    virtual ~mexternalForce();


    // Member Functions

        //- Accumulate the retraint internal mjoint forces into the tau field and
        //  external forces into the fx field
        virtual void restrain
        (
            scalarField& tau,
            Field<spatialVector>& fx,
            const mrigidBodyModelState& state
        ) const;

        //- Update properties from given dictionary
        virtual bool read(const dictionary& dict);

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mrestraints
} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
