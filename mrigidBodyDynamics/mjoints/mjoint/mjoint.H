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

Namespace
    Foam::RBD::mjoints

Group
    grpRigidBodyDynamicsJoints

Description
    Namespace for rigid-body mjoints

Class
    Foam::RBD::mjoint

Description
    Abstract base-class for all rigid-body mjoints.

    Reference:
    \verbatim
        Featherstone, R. (2008).
        Rigid body dynamics algorithms.
        Springer.
        Chapter 4.
    \endverbatim

SourceFiles
    mjointI.H
    mjoint.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_joint_H
#define RBD_joint_H

#include "List.H"
#include "spatialVector.H"
#include "compactSpatialTensor.H"
#include "CompactSpatialTensorT.H"
#include "spatialTransform.H"
#include "quaternion.H"
#include "scalarField.H"
#include "runTimeSelectionTables.H"

namespace Foam
{
namespace RBD
{

// Forward declaration of classes
class mrigidBodyModel;

// Forward declaration of friend functions and operators
class mjoint;

inline Ostream& operator<<(Ostream&, const mjoint&);


/*---------------------------------------------------------------------------*\
                         Class mjoint Declaration
\*---------------------------------------------------------------------------*/

class mjoint
{

protected:

    // Protected data

    //- Joint motion sub-space
    List<spatialVector> S_;

    //- Index of this mjoint in the mrigidBodyModel
    label index_;

    //- Index of this mjoints data in the mrigidBodyModel state
    label qIndex_;


private:

    // Private member functions to be used by mrigidBodyModel

        //- Allow the mrigidBodyModel to set the index for this mjoint
        label& index()
        {
            return index_;
        }

        //- Allow the mrigidBodyModel to set the qIndex for this mjoint
        label& qIndex()
        {
            return qIndex_;
        }


public:

    //- Allow the mrigidBodyModel class to set the mjoint indices
    friend class mrigidBodyModel;

    //- Joint state returned by jcalc
    class XSvc
    {
    public:

        //- The mjoint transformation
        spatialTransform X;

        //- The mjoint motion sub-space (3-DoF)
        compactSpatialTensor S;

        //- The mjoint motion sub-space (1-DoF)
        spatialVector S1;

        //- The constrained mjoint velocity
        spatialVector v;

        //- The constrained mjoint acceleration correction
        //  due to changes in the motion sub-space S
        spatialVector c;

        //- Null constructor
        XSvc()
        :
            X(),
            v(Zero),
            c(Zero)
        {}
    };


public:

    //- Runtime type information
    TypeName("mjoint");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            mjoint,
            dictionary,
            (const dictionary& dict),
            (dict)
        );


    // Constructors

        //- Construct mjoint setting the size of the motion sub-space
        //  to the given degrees of freedom of the mjoint
        inline mjoint(const label nDoF);

        //- Clone this mjoint (needed by PtrList)
        virtual autoPtr<mjoint> clone() const = 0;

        class iNew
        {

        public:

            iNew()
            {}

            inline autoPtr<mjoint> operator()(Istream& is) const;
        };


    //- Destructor
    virtual ~mjoint();


    // Selectors

        //- Simple selector to return an autoPtr<mjoint> of the given mjoint*
        static autoPtr<mjoint> New(mjoint* jointPtr);

        //- Select from dictionary
        static autoPtr<mjoint> New(const dictionary& dict);


    // Member Functions

        //- Return the number of degrees of freedom in this mjoint
        inline label nDoF() const;

        //- Return true if this mjoint describes rotation using a quaternion
        inline virtual bool unitQuaternion() const;

        //- Return the index of this mjoint in the model
        inline label index() const;

        //- Return start index for the state variables for this mjoint
        //  in the mrigidBodyModel state fields
        inline label qIndex() const;

        //- Return the mjoint motion sub-space
        inline const List<spatialVector>& S() const;

        //- Update the mrigidBodyModel state for the mjoint given
        //  the mjoint state q, w and velocity qDot
        virtual void jcalc
        (
            XSvc& J,
            const scalarField& q,
            const scalarField& qDot
        ) const = 0;

        //- Write
        virtual void write(Ostream&) const;


    // Member Operators

        //- Return the unit quaternion for this mjoint
        //  if it uses a quaternion representation for rotation
        inline quaternion unitQuaternion
        (
            const scalarField& q
        ) const;

        //- Set the unit quaternion for this mjoint
        //  if it uses a quaternion representation for rotation
        inline void unitQuaternion
        (
            const quaternion& quat,
            scalarField& q
        ) const;


    // Ostream Operator

        friend Ostream& operator<<(Ostream&, const mjoint&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mjointI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
