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
#include "mrigidBodyModel.H"
#include "addToRunTimeSelectionTable.H"
#include "mOrbitalMotion.H"
#include "Time.H"
 
namespace Foam
{
namespace RBD
{
namespace mrestraints
{
    defineTypeNameAndDebug(mOrbitalMotion, 0);
    addToRunTimeSelectionTable
    (
        mrestraint,
        mOrbitalMotion,
        dictionary
    );
}
}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
 
Foam::RBD::mrestraints::mOrbitalMotion::mOrbitalMotion
(
    const word& name,
    const dictionary& dict,
    const mrigidBodyModel& model
)
:
    mrestraint(name, dict, model),
    amp_(0),
    omega_(0),
    g_(0),
    m_(0)
{
    read(dict);
}
// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //
 
Foam::RBD::mrestraints::mOrbitalMotion::~mOrbitalMotion()
{}
// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::RBD::mrestraints::mOrbitalMotion::restrain
(
    scalarField& tau,
    Field<spatialVector>& fx,
    const mrigidBodyModelState& state
) const
{
    scalar t = model_.time().value();

    vector moment = vector::zero;
    vector force(
        0,
        amp_ *m_*omega_*omega_*Foam::cos(omega_ * t),
        amp_ *m_*omega_*omega_*Foam::sin(omega_ * t)
    );
    force += vector(0, 0, m_ * g_);

        Info  << " Amplitude" << amp_
        << " omega" << omega_
            << " force " << force
            << " moment " << moment
            << endl;
 
    // Accumulate the force for the restrained body
    fx[bodyIndex_] += spatialVector(moment, force);
}
bool Foam::RBD::mrestraints::mOrbitalMotion::read
(
    const dictionary& dict
)
{
    mrestraint::read(dict);
    coeffs_.readEntry("Amplitude", amp_);
    coeffs_.readEntry("omega", omega_);
    coeffs_.readEntry("g", g_);
    coeffs_.readEntry("m", m_);
    return true;
}
 
    void Foam::RBD::mrestraints::mOrbitalMotion::write(Ostream& os) const
    {
        mrestraint::write(os);  // Write base class (e.g., body name, index)
    
        os.writeEntry("Amplitude", amp_);
        os.writeEntry("omega", omega_);
        os.writeEntry("m", m_);
        os.writeEntry("g", g_);
    }
    
 
 
 