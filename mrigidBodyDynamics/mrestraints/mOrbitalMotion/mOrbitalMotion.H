#ifndef OrbitalMotion_H
#define OrbitalMotion_H

#include "mrigidBodyRestraint.H"

namespace Foam
{
namespace RBD
{
namespace mrestraints
{

class mOrbitalMotion : public mrestraint
{
    // Private data
    scalar amp_;    // Amplitude of orbital motion
    scalar omega_;  // Angular frequency
    scalar g_;      // Gravitational acceleration
    scalar m_;      // Mass of the body

public:

    //- Runtime type information
    TypeName("mOrbitalMotion");

    //- Constructor
    mOrbitalMotion
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
                new mOrbitalMotion(*this)
            );
        }
 
    //- Destructor
    virtual ~mOrbitalMotion();

    //- Apply the force and moment for this mrestraint
    virtual void restrain
    (
        scalarField& tau,
        Field<spatialVector>& fx,
        const mrigidBodyModelState& state
    ) const;

    //- Read dictionary settings
    virtual bool read(const dictionary& dict);
    virtual void write(Ostream&) const;
};

} // namespace mrestraints
} // namespace RBD
} // namespace Foam

#endif
