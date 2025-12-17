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
    Foam::RBD::mrestraints::mlinearSpring

Group
    grpRigidBodyDynamicsRestraints

Description
    Linear spring mrestraint.

SourceFiles
    mlinearSpring.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_restraints_linearSpring_H
#define RBD_restraints_linearSpring_H

#include "mrigidBodyRestraint.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{
namespace mrestraints
{

/*---------------------------------------------------------------------------*\
                          Class mlinearSpring Declaration
\*---------------------------------------------------------------------------*/

class mlinearSpring
:
    public mrestraint
{
    // Private data

        //- Anchor point, where the spring is attached to an immovable
        //  object
        point anchor_;

        //- Reference point of attachment to the solid body
        point refAttachmentPt_;

        //- Spring stiffness coefficient [N/m]
        scalar stiffness_;

        //- Damping coefficient [Ns/m]
        scalar damping_;

        //- Rest length - length of spring when no forces are applied to it
        scalar restLength_;


public:

    //- Runtime type information
    TypeName("mlinearSpring");


    // Constructors

        //- Construct from components
        mlinearSpring
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
                new mlinearSpring(*this)
            );
        }


    //- Destructor
    virtual ~mlinearSpring();


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
