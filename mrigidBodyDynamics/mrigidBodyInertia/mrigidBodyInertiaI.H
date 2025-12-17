/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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

#include "spatialTransform.H"
#include "transform.H"
#include "dictionary.H"

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

inline Foam::symmTensor Foam::RBD::mrigidBodyInertia::Ioc
(
    const scalar m,
    const vector& c
)
{
    return m*(Foam::I*magSqr(c) - sqr(c));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline Foam::RBD::mrigidBodyInertia::mrigidBodyInertia()
:
    m_(Zero),
    c_(Zero),
    Ic_(Zero)
{}


inline Foam::RBD::mrigidBodyInertia::mrigidBodyInertia
(
    const scalar m,
    const vector& c,
    const symmTensor& Ic
)
:
    m_(m),
    c_(c),
    Ic_(Ic)
{}


inline Foam::RBD::mrigidBodyInertia::mrigidBodyInertia(const dictionary& dict)
:
    m_(dict.get<scalar>("mass")),
    c_(dict.get<vector>("centreOfMass")),
    Ic_(dict.get<symmTensor>("inertia"))
{}


inline Foam::RBD::mrigidBodyInertia::mrigidBodyInertia(const spatialTensor& st)
:
    m_(st(3, 3)),
    c_(vector(-st(1, 5), st(0, 5), -st(0, 4))/m_),
    Ic_(symm(st.block<tensor, 0, 0>()()) - Ioc())
{}


inline Foam::RBD::mrigidBodyInertia::mrigidBodyInertia(Istream& is)
:
    m_(readScalar(is)),
    c_(is),
    Ic_(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline Foam::scalar Foam::RBD::mrigidBodyInertia::m() const
{
    return m_;
}

inline const Foam::vector& Foam::RBD::mrigidBodyInertia::c() const
{
    return c_;
}

inline const Foam::symmTensor& Foam::RBD::mrigidBodyInertia::Ic() const
{
    return Ic_;
}

inline Foam::symmTensor Foam::RBD::mrigidBodyInertia::Ioc() const
{
    return Ioc(m_, c_);
}

inline Foam::symmTensor Foam::RBD::mrigidBodyInertia::Icc(const vector& c) const
{
    return Ioc(m_, c - c_);
}

inline Foam::symmTensor Foam::RBD::mrigidBodyInertia::Io() const
{
    return Ic_ + Ioc();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline Foam::RBD::mrigidBodyInertia::operator spatialTensor() const
{
    tensor mcStar(m_*(*c_));

    return spatialTensor
    (
        Io(),   mcStar,
       -mcStar, m_*I
    );
}


// * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * * //

inline Foam::Istream& Foam::RBD::operator>>
(
    Istream& is,
    mrigidBodyInertia& rbi
)
{
    is  >> rbi.m_ >> rbi.c_ >> rbi.Ic_;
    return is;
}


inline Foam::Ostream& Foam::RBD::operator<<
(
    Ostream& os,
    const mrigidBodyInertia& rbi
)
{
    os  << rbi.m_ << nl << rbi.c_ << nl << rbi.Ic_ << endl;
    return os;
}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

namespace Foam
{
namespace RBD
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Return the rigid-body inertia of the combined body
inline mrigidBodyInertia operator+
(
    const mrigidBodyInertia& rbi1,
    const mrigidBodyInertia& rbi2
)
{
    const scalar m12 = rbi1.m() + rbi2.m();
    const vector c12 = (rbi1.m()*rbi1.c() + rbi2.m()*rbi2.c())/m12;

    return mrigidBodyInertia
    (
        m12,
        c12,
        rbi1.Ic() + rbi1.Icc(c12) + rbi2.Ic() + rbi2.Icc(c12)
    );
}


//- Inner-product with a spatialVector (e.g. velocity returning the momentum)
inline spatialVector operator&
(
    const mrigidBodyInertia& rbi,
    const spatialVector& sv
)
{
    const vector av(sv.w());
    const vector lv(sv.l());

    return spatialVector
    (
        (rbi.Io() & av) + rbi.m()*(rbi.c() ^ lv),
        rbi.m()*lv - rbi.m()*(rbi.c() ^ av)
    );
}


//- Return (^BX_A)^* I ^AX_B
inline mrigidBodyInertia transform
(
    const spatialTransform& X,
    const mrigidBodyInertia& I
)
{
    const vector Xc((X.E().T() & I.c()) + X.r());

    return mrigidBodyInertia
    (
        I.m(),
        Xc,
        transform(X.E().T(), I.Ic())
    );
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RBD
} // End namespace Foam


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline Foam::scalar Foam::RBD::mrigidBodyInertia::kineticEnergy
(
    const spatialVector& v
)
{
    return 0.5*(v && (*this & v));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void Foam::RBD::mrigidBodyInertia::operator+=
(
    const mrigidBodyInertia& rbi
)
{
    *this = *this + rbi;
}


// ************************************************************************* //
