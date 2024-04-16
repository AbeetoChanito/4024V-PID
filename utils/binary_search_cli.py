class InputState:
  HIGH = 0
  LOW = 1
  STOP = 2

  @staticmethod
  def get_input_state():
    text = input("input state: ")

    if text == "high":
      return InputState.HIGH
    if text == "low":
      return InputState.LOW
    if text == "stop":
      return InputState.STOP
      
    print("invalid input, try again")
    return InputState.get_input_state()

def state_2X(k, k_name):
  while True:
    k *= 2
    print(f"(stage 2X) try {k_name}: {k:.2f}")

    state = InputState.get_input_state()
    
    if state == InputState.HIGH:
      k /= 2
      return k

    if state == InputState.STOP:
      return k

def state_binary_search(k, k_name):
  last_high = k * 2
  last_low = 0

  while True:
    print(f"(stage binary search) try {k_name}: {k:.2f}")

    state = InputState.get_input_state()

    if state == InputState.HIGH:
      last_k = k
      k = (k + last_low) / 2
      last_high = last_k
    elif state == InputState.LOW:
      last_k = k
      k = (last_high + k) / 2
      last_low = last_k
    elif state == InputState.STOP:
      return k

def state_tune_constant(k, k_name):
  k = state_2X(k, k_name)
  k = state_binary_search(k, k_name)
  return k

kp = float(input("(stage begin) input kp: "))
kd = float(input("(stage begin) input kd: "))

i = 0

while True:
  kp = state_tune_constant(kp, "kp")
  kd = state_tune_constant(kd, "kd")
  print(f"(stage {i + 1}) kp: {kp:.2f}, kd: {kd:.2f}")
  i += 1