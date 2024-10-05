This code is for DFA minimization, where a transition table is taken as input at runtime.
Caution: It works only for two input symbols. For further modifications, you need to add a four-equivalence method that contains 16 for loops and split the thirdEqui 2D matrix accordingly.
Caution: If you are modifying the code, kindly take care of the 3D matrix used here.

Idea and approach
 -This code is based on a procedural way of finding minimization.
 
 -First, find 0 equivalence, then 1, and so on.
 
 -Storing all the equivalence elements in the final 3D matrix and also using the incol-2D and inrow 1D for storing limits of the valid elements contained in the 
  equivalence-final table. This prevents you from grabbing garbage values.
