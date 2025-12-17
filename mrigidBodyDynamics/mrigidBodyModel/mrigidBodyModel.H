/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
    Copyright (C) 2019 OpenCFD Ltd.
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
    Foam::RBD::mrigidBodyModel

Description
    Basic rigid-body model representing a system of rigid-mbodies connected by
    1-6 DoF mjoints.

    This class holds various body and mjoint state fields needed by the
    kinematics and forward-dynamics algorithms presented in

    reference:
    \verbatim
        Featherstone, R. (2008).
        Rigid body dynamics algorithms.
        Springer.
        Chapter 4.
    \endverbatim

SourceFiles
    mrigidBodyModel.C
    kinematics.C
    forwardDynamics.C

\*---------------------------------------------------------------------------*/

#ifndef RBD_mrigidBodyModel_H
#define RBD_mrigidBodyModel_H

#include "mrigidBody.H"
#include "msubBody.H"
#include "mjoint.H"
#include "mcompositeJoint.H"
#include "PtrList.H"
#include "HashTable.H"

namespace Foam
{

// Forward declaration of friend functions and operators
class Time;

namespace RBD
{

// Forward declaration of friend functions and operators
class mrigidBodyModel;

Ostream& operator<<(Ostream&, const mrigidBodyModel&);

class mrigidBodyModelState;
class mrestraint;


/*---------------------------------------------------------------------------*\
                         Class mrigidBodyModel Declaration
\*---------------------------------------------------------------------------*/

class mrigidBodyModel
{
    // Private member functions

        //- Initialize the model with the root-body
        //  which is a fixed massless bodyat the origin.
        void initializeRootBody();

        //- Resize the state fields following the joining of a body
        void resizeState();

        //- Convert the body with given ID into a mcomposite-body
        void makeComposite(const label bodyID);

        //- Add mrestraints to the motion
        void addRestraints(const dictionary& dict);

protected:

        //- Reference to time database
        const Time& time_;

    // Protected data representing the model structure

        //- List of the mbodies.
        //  The 0'th body represents the fixed origin and is constructed
        //  automatically.  The subsequent (moving) mbodies are appended by the
        //  join member function.
        PtrList<mrigidBody> bodies_;

        //- Bodies may be merged into existing mbodies, the inertia of which is
        //  updated to represent the combined body which is more efficient than
        //  attaching them with fixed mjoints.  These 'merged' mbodies are held on
        //  this list.
        PtrList<msubBody> mergedBodies_;

        //- Lookup-table of the IDs of the mbodies
        HashTable<label> bodyIDs_;

        //- List of indices of the parent of each body
        DynamicList<label> lambda_;

        //- Each body it attached with a mjoint which are held on this list.
        PtrList<mjoint> joints_;

        //- Transform from the parent body frame to the mjoint frame.
        DynamicList<spatialTransform> XT_;

        //- The number of degrees of freedom of the model
        //  used to set the size of the of mjoint state fields q, qDot and qDdot.
        label nDoF_;

        //- True if any of the mjoints using quaternions
        bool unitQuaternions_;

        //- Motion mrestraints
        PtrList<mrestraint> restraints_;


    // Other protected member data

        //- Acceleration due to gravity
        vector g_;


    // Mutable transforms maintained by kinematics and forward-dynamics

        //- Transform from the parent body to the current body
        mutable DynamicList<spatialTransform> Xlambda_;

        //- Transform for external forces to the mbodies reference frame
        mutable DynamicList<spatialTransform> X0_;


    // Mutable kinematic body state fields

        //- The spatial velocity of the mbodies
        mutable DynamicList<spatialVector> v_;

        //- The spatial acceleration of the mbodies
        mutable DynamicList<spatialVector> a_;

        //- The velocity dependent spatial acceleration of the mjoints
        mutable DynamicList<spatialVector> c_;


    // Mutable state fields needed by the forward-dynamics algorithm

        //- Velocity-product acceleration

        //- Articulated body inertia
        mutable DynamicList<spatialTensor> IA_;

        //- Articulated body bias force
        mutable DynamicList<spatialVector> pA_;


    // Mutable mjoint state fields

        //- Motion subspace for mjoints with 3 degrees of freedom
        mutable DynamicList<compactSpatialTensor> S_;

        //- Motion subspace for mjoints with 1 degrees of freedom
        mutable DynamicList<spatialVector> S1_;

        //- Sub-expression IA.S in the forward-dynamics algorithm
        mutable DynamicList<compactSpatialTensor> U_;

        //- Sub-expression IA.S1 in the forward-dynamics algorithm
        mutable DynamicList<spatialVector> U1_;

        //- Sub-expression (S^T.U)^-1 in the forward-dynamics algorithm
        mutable DynamicList<tensor> Dinv_;

        //- Sub-expression tau - S^T.pA in the forward-dynamics algorithm
        mutable DynamicList<vector> u_;


    // Protected member functions

        //- Join the given body to the parent with ID parentID via the given
        //  mjoint with transform from the parent frame to the mjoint frame XT.
        virtual label join_
        (
            const label parentID,
            const spatialTransform& XT,
            autoPtr<mjoint> jointPtr,
            autoPtr<mrigidBody> bodyPtr
        );


public:

    //- Runtime type information
    TypeName("mrigidBodyModel");
    scalar amplitude_;
    scalar omega_;

    // Constructors

        //- Null-constructor which adds the single root-body at the origin
        mrigidBodyModel(const Time& time);

        //- Construct from dictionary
        mrigidBodyModel(const Time& time, const dictionary& dict);


    //- Destructor
    virtual ~mrigidBodyModel();


    // Member Functions

        //- Return the time
        inline const Time& time() const;

        //- Return the number of mbodies in the model (mbodies().size())
        inline label nBodies() const;

        //- Return the list of the mbodies in the model
        inline PtrList<mrigidBody> mbodies() const;

        //- List of indices of the parent of each body
        inline const DynamicList<label>& lambda() const;

        //- Return the list of mjoints in the model
        inline const PtrList<mjoint>& mjoints() const;

        //- Return the number of degrees of freedom of the model
        //  used to set the size of the of mjoint state fields q, qDot and qDdot.
        inline label nDoF() const;

        //- Return true if any of the mjoints using quaternions
        inline bool unitQuaternions() const;

        //- Return the acceleration due to gravity
        inline const vector& g() const;

        //- Allow the acceleration due to gravity to be set
        //  after model construction
        inline vector& g();

        //- Return the name of body with the given ID
        inline const word& name(const label bodyID) const;

        //- Return the inertia of body i
        inline const mrigidBodyInertia& I(const label i) const;

        //- Return the spatial velocity of the mbodies
        inline const spatialVector& v(const label i) const;

        //- Return the spatial acceleration of the mbodies
        inline const spatialVector& a(const label i) const;

        //- Join the given body to the parent with ID parentID via the given
        //  mjoint with transform from the parent frame to the mjoint frame XT.
        virtual label join
        (
            const label parentID,
            const spatialTransform& XT,
            autoPtr<mjoint> jointPtr,
            autoPtr<mrigidBody> bodyPtr
        );

        //- Join the given body to the parent with ID parentID via the given
        //  mcomposite mjoint (specified as a list of co-located mjoints) with
        //  transform from the parent frame to the mjoint frame XT.
        //  Composite joins are useful to represent complex mjoints with degrees
        //  of freedom other than 1 or 3 which are directly supported.
        label join
        (
            const label parentID,
            const spatialTransform& XT,
            autoPtr<mjoints::mcomposite> cJoint,
            autoPtr<mrigidBody> bodyPtr
        );

        //- Merge the given body with transform X into the parent with ID
        //  parentID.  The parent body assumes the properties of the combined
        //  body (inertia etc.) and the merged body is held on a
        //  separate list for reference.
        label merge
        (
            const label parentID,
            const spatialTransform& X,
            autoPtr<mrigidBody> bodyPtr
        );

        //- Return true if the body with given ID has been merged with a parent
        inline bool merged(label bodyID) const;

        //- Return the ID of the master body for a sub-body otherwise
        //  return the given body ID
        inline label master(label bodyID) const;

        //- Return the index of the merged body in the mergedBody list
        //  from the given body ID
        inline label mergedBodyIndex(const label mergedBodyID) const;

        //- Return the merged body ID for the given merged body index
        //  in the mergedBody list
        inline label mergedBodyID(const label mergedBodyIndex) const;

        //- Return the merged body for the given body ID
        inline const msubBody& mergedBody(label mergedBodyID) const;

        //- Return the ID of the body with the given name
        inline label bodyID(const word& name) const;

        //- Return the current transform to the global frame for the given body
        spatialTransform X0(const label bodyId) const;

        // Find the corresponding point in the master body frame
        vector masterPoint(const label bodyID, const vector& p) const;

        //- Return the velocity of the given point on the given body
        spatialVector v(const label bodyID, const vector& p) const;

        //- Apply the mrestraints and accumulate the internal mjoint forces
        //  into the tau field and external forces into the fx field
        void applyRestraints
        (
            scalarField& tau,
            Field<spatialVector>& fx,
            const mrigidBodyModelState& state
        ) const;

        //- Calculate the mjoint acceleration qDdot from the mjoint state q,
        //  velocity qDot, internal force tau (in the mjoint frame) and
        //  external force fx (in the global frame) using the articulated body
        //  algorithm (Section 7.3 and Table 7.1)
        void forwardDynamics
        (
            mrigidBodyModelState& state,
            const scalarField& tau,
            const Field<spatialVector>& fx
        ) const;

        //- Correct the velocity and acceleration of the mbodies in the model
        //  from the given mjoint state fields following an integration step
        //  of the forwardDynamics
        void forwardDynamicsCorrection(const mrigidBodyModelState& state) const;

        //- Write
        virtual void write(Ostream&) const;

        //- Read coefficients dictionary and update system parameters,
        //  mrestraints but not the current state
        bool read(const dictionary& dict);


    // Ostream Operator

        friend Ostream& operator<<(Ostream&, const mrigidBodyModel&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RBD
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mrigidBodyModelI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
