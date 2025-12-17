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
    Foam::RBD::mrestraints::mlinearDamper

Group
    grpRigidBodyDynamicsRestraints

Description
    Linear damper mrestraint.  Operates in the local frame of the body.

SourceFiles
    mlinearDamper.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_restraints_linearDamper_H
#define RBD_restraints_linearDamper_H

#include "mrigidBodyRestraint.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mrestraints
{

/*---------------------------------------------------------------------------*\
                          Class mlinearDamper Declaration
\*---------------------------------------------------------------------------*/

class mlinearDamper
:
    public mrestraint
{
    // Private data

        //- Damping coefficient [Ns/m]
        scalar coeff_;


public:

    //- Runtime type information
    TypeName("mlinearDamper");


    // Constructors

        //- Construct from components
        mlinearDamper
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
                new mlinearDamper(*this)
            );
        }


    //- Destructor
    virtual ~mlinearDamper();


    // Member Functions

        //- Accumulate the mrestraint internal mjoint forces into the tau field and
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
