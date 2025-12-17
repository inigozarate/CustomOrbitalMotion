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

inline Foam::RBD::mrigidBody::mrigidBody
(
    const word& name,
    const scalar& m,
    const vector& c,
    const symmTensor& Ic
)
:
    mrigidBodyInertia(m, c, Ic),
    name_(name)
{}


inline Foam::RBD::mrigidBody::mrigidBody
(
    const word& name,
    const mrigidBodyInertia& rbi
)
:
    mrigidBodyInertia(rbi),
    name_(name)
{}


inline Foam::RBD::mrigidBody::mrigidBody
(
    const word& name,
    const dictionary& dict
)
:
    mrigidBodyInertia(dict),
    name_(name)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const Foam::word& Foam::RBD::mrigidBody::name() const
{
    return name_;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline Foam::Ostream& Foam::RBD::operator<<(Ostream& os, const mrigidBody& rb)
{
    rb.write(os);
    return os;
}


// ************************************************************************* //
