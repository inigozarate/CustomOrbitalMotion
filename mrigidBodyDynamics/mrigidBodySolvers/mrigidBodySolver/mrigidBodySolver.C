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

#include "mrigidBodySolver.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{

    defineTypeNameAndDebug(mrigidBodySolver, 0);
    defineRunTimeSelectionTable(mrigidBodySolver, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::RBD::mrigidBodySolver::mrigidBodySolver(mrigidBodyMotion& body)
:
    model_(body)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::RBD::mrigidBodySolver::~mrigidBodySolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::RBD::mrigidBodySolver::correctQuaternionJoints()
{
    if (model_.unitQuaternions())
    {
        forAll(model_.mjoints(), i)
        {
            const label qi = model_.mjoints()[i].qIndex();

            if (model_.mjoints()[i].unitQuaternion())
            {
                // Calculate the change in the unit quaternion
                vector dv((q().block<vector>(qi) - q0().block<vector>(qi)));
                scalar magDv = mag(dv);

                if (magDv > SMALL)
                {
                    // Calculate the unit quaternion corresponding to the change
                    quaternion dQuat(dv/magDv, cos(magDv), true);

                    // Transform the previous time unit quaternion
                    quaternion quat
                    (
                        model_.mjoints()[i].unitQuaternion(q0())*dQuat
                    );
                    quat.normalise();

                    // Update the mjoint unit quaternion
                    model_.mjoints()[i].unitQuaternion(quat, q());
                }
            }
        }
    }
}


// ************************************************************************* //
