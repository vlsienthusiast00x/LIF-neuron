# Leaky Integrate-and-Fire Neuron

A minimal C implementation of the **leaky integrate-and-fire (LIF)** neuron model — one of the most widely used spiking neuron models in computational neuroscience.

## Overview

The LIF model captures the essential dynamics of a biological neuron: a membrane voltage that integrates synaptic input, leaks back toward rest, and fires a spike when it crosses a threshold. Despite its simplicity, it reproduces realistic firing patterns including refractory periods and rate adaptation.

The membrane potential evolves according to:

$$\tau_m \frac{dV}{dt} = -(V - V_{rest}) + R \cdot I(t)$$

When $V \geq V_{th}$, a spike is emitted and $V$ is reset to $V_{rest}$, followed by an absolute refractory period $t_{ref}$.

## Parameters

| Parameter | Symbol | Value | Unit | Description |
|-----------|--------|-------|------|-------------|
| Timestep | $\Delta t$ | 0.1 | ms | Euler integration step |
| Resting potential | $V_{rest}$ | −70 | mV | Baseline membrane voltage |
| Threshold | $V_{th}$ | −55 | mV | Spike threshold |
| Time constant | $\tau_m$ | 20 | ms | Membrane leak time constant |
| Resistance | $R$ | 10 | MΩ | Membrane resistance |
| Refractory period | $t_{ref}$ | 2 | ms | Post-spike silence duration |

## Simulation

The simulation runs for **50 ms** (500 steps × 0.1 ms). A constant input current of **3.5 nA** is injected from t = 5 ms to t = 35 ms, driving the neuron to fire repeatedly. Outside this window, the membrane decays passively back to rest.

## Build & Run

No dependencies — just a C compiler.

```bash
gcc -o lif lif.c -lm
./lif
```

Expected output (every 10th step):

```
t=  0.0 ms | V= -70.00 mV | .
t=  1.0 ms | V= -70.00 mV | .
t=  5.0 ms | V= -70.00 mV | .
t=  6.0 ms | V= -68.25 mV | .
...
t= 14.0 ms | V= -70.00 mV | SPIKE
...
```

https://github.com/user-attachments/assets/343c64ad-6f10-4cd8-949c-bdc49484104b


## Key Concepts

**Subthreshold dynamics** — below threshold, $V$ charges exponentially toward the steady state $V_{rest} + R \cdot I$. The time constant $\tau_m$ controls how quickly it gets there.

**Firing threshold** — once $V$ reaches $V_{th}$, a spike is recorded and $V$ is immediately reset. The actual spike waveform is not modelled; only the event time matters.

**Refractory period** — after a spike, the neuron is clamped at $V_{rest}$ for $t_{ref}$ ms, setting a hard upper bound on firing rate of $1000 / t_{ref}$ Hz.

**Firing rate** — with the default parameters the neuron fires roughly 55–60 Hz during the current injection window.

## References

- Gerstner, W. & Kistler, W. (2002). *Spiking Neuron Models*. Cambridge University Press.
- Dayan, P. & Abbott, L.F. (2001). *Theoretical Neuroscience*. MIT Press. Ch. 5.
- [Scholarpedia — Integrate-and-fire neuron](http://www.scholarpedia.org/article/Integrate-and-fire_neuron)
