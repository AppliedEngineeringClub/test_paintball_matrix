#!/usr/bin/env bash
set -euo pipefail

# Solenoids
SOL_GPIOS=(1 7 0 3 19 18 15 )

# Servos (software PWM handled elsewhere)
SERVO_GPIOS=(6 2)

export_gpio() {
  local g="$1"
  if [[ ! -d "/sys/class/gpio/gpio${g}" ]]; then
    echo "$g" > /sys/class/gpio/export 2>/dev/null || true
    sleep 0.05
  fi
}

setup_output_low() {
  local g="$1"
  export_gpio "$g"
  echo out > "/sys/class/gpio/gpio${g}/direction"
  echo 0   > "/sys/class/gpio/gpio${g}/value"
}

echo "[+] Setting up SOLENOIDS: ${SOL_GPIOS[*]}"
for g in "${SOL_GPIOS[@]}"; do
  setup_output_low "$g"
done

echo "[+] Setting up SERVOS (idle LOW): ${SERVO_GPIOS[*]}"
for g in "${SERVO_GPIOS[@]}"; do
  setup_output_low "$g"
done

echo "[OK] All solenoid and servo GPIOs configured and set LOW."
