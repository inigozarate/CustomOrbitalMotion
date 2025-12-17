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

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline Foam::RBD::msubBody::msubBody
(
    const autoPtr<mrigidBody>& bodyPtr,
    const word& masterName,
    const label masterID,
    const spatialTransform& masterXT
)
:
    body_(bodyPtr),
    masterName_(masterName),
    masterID_(masterID),
    masterXT_(masterXT)
{}


inline Foam::autoPtr<Foam::RBD::msubBody> Foam::RBD::msubBody::clone() const
{
    return autoPtr<msubBody>::New(*this);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const Foam::RBD::mrigidBody& Foam::RBD::msubBody::body() const
{
    return *body_;
}


inline const Foam::word& Foam::RBD::msubBody::name() const
{
    return body_->name();
}


inline const Foam::word& Foam::RBD::msubBody::masterName() const
{
    return masterName_;
}


inline Foam::label Foam::RBD::msubBody::masterID() const
{
    return masterID_;
}


inline const Foam::spatialTransform& Foam::RBD::msubBody::masterXT() const
{
    return masterXT_;
}


// ************************************************************************* //
