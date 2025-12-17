/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2017 OpenFOAM Foundation
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

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const Foam::scalarField& Foam::RBD::mrigidBodyModelState::q() const
{
    return q_;
}


inline const Foam::scalarField& Foam::RBD::mrigidBodyModelState::qDot() const
{
    return qDot_;
}


inline const Foam::scalarField& Foam::RBD::mrigidBodyModelState::qDdot() const
{
    return qDdot_;
}


inline Foam::scalar Foam::RBD::mrigidBodyModelState::t() const
{
    return t_;
}


inline Foam::scalar Foam::RBD::mrigidBodyModelState::deltaT() const
{
    return deltaT_;
}


inline Foam::scalarField& Foam::RBD::mrigidBodyModelState::q()
{
    return q_;
}


inline Foam::scalarField& Foam::RBD::mrigidBodyModelState::qDot()
{
    return qDot_;
}


inline Foam::scalarField& Foam::RBD::mrigidBodyModelState::qDdot()
{
    return qDdot_;
}


inline Foam::scalar& Foam::RBD::mrigidBodyModelState::deltaT()
{
    return deltaT_;
}


inline Foam::scalar& Foam::RBD::mrigidBodyModelState::t()
{
    return t_;
}


// ************************************************************************* //
