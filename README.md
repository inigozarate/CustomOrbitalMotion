[DocMotionLaw.MD](https://github.com/user-attachments/files/24239820/DocMotionLaw.MD)
## Motion law

The orbital motion of the tank is prescribed through the acceleration
components

$$
a_x(t) = a\,\omega^2 \cos(\omega t),
\qquad
a_z(t) = -a\,\omega^2 \sin(\omega t).
$$

These accelerations correspond to a circular trajectory of radius \(a\)
in the \(x\text{–}z\) plane.

Since the tank motion is controlled through acceleration, the position
\(\mathbf{p}(t)\) is obtained by time integration. Assuming zero initial
velocity,

$$
\mathbf{v}(0) = \mathbf{0},
$$

the integration of the acceleration yields

$$
p_x(t) = a + a\cos(\omega t),
\qquad
p_z(t) = a\sin(\omega t).
$$

The constant term in \(p_x(t)\) represents an offset introduced by the
initial conditions and ensures a closed circular orbit centered at
\((a,0)\) in the \(x\text{–}z\) plane.

## Control variable

The tank motion is controlled by prescribing the acceleration in time.
The corresponding velocity and position are obtained by numerical time
integration using a Newmark scheme, ensuring consistency between
acceleration, velocity and displacement.

## Initial conditions and offset

The initial conditions are prescribed as

$$
\mathbf{v}(0) = \mathbf{0}.
$$

When integrating the imposed acceleration with zero initial velocity,
a constant offset naturally appears in the position along the \(x\)
direction. This offset is given by

$$
O = a,
$$

and is required to recover the correct orbital trajectory. Without this
offset, the trajectory would be not be centerd on (0,0)
## OpenFOAM code 
In the folder:
/mrigidBodyDynamics/mrigidBodyMotion/mrigidBodyMotion.C

In the function forward dynamics the following code is implemented:

```cpp

void Foam::RBD::mrigidBodyMotion::forwardDynamics
(
    mrigidBodyModelState& state,
    const scalarField& tau,
    const Field<spatialVector>& fx
) const


{
    scalarField qDdotPrev = state.qDdot();
    mrigidBodyModel::forwardDynamics(state, tau, fx);

    scalar aRelax = 1;
    if (aRelax_)
    {
        aRelax = aRelax_->value(motionState_.t());
    }
// Get amplitude and frequency from the dictionary


// Calculate angular frequency (omega = 2 * pi * frequency)

// Current simulation time
scalar t = motionState_.t();

// Prescribed sinusoidal acceleration
scalar acc_x = amplitude_ * omega_*omega_ * Foam::cos(omega_ * t);
scalar acc_z = -amplitude_ * omega_*omega_ * Foam::sin(omega_ * t);
Info <<"Modified forward dynamics running"<< endl;
// Set acceleration clearly for each degree of freedom

forAll(state.qDdot(), i)
{
    if (i == 0)
    {
    state.qDdot()[i] = acc_x;
    state.q()[i]
    Info<< "qDdot["<<i<<"]="<<state.qDdot()[i]<<nl;
        Info<< "qDdot["<<i<<"]="<<state.qDdot()[i]<<nl;
    }
    else if (i == 2)
    {
        state.qDdot()[i] = acc_z;
         Info<< "qDdot["<<i<<"]="<<state.qDdot()[i]<<nl;
        Info<< "qDdot["<<i<<"]="<<state.qDdot()[i]<<nl;
    }
    else
    {
        Info<< "qDdot["<<i<<"]="<<state.qDdot()[i]<<nl;
        Info<< "qDdot["<<i<<"]="<<state.qDdot()[i]<<nl;
        state.qDdot()[i] = aDamp_*(aRelax*state.qDdot()[i] + (1-aRelax)*qDdotPrev[i]);
    }
}

}

```
