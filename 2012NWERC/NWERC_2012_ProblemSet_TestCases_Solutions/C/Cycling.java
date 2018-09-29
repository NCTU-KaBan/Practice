// @EXPECTED_RESULTS@: CORRECT

import java.io.*;
import java.util.*;

public class Cycling {

    public static void main(String [] args){
       run();
    }

    public static void run(){
      InputStream is = null;
      try{
         is = System.in; // in case you want to read from System.in
         Scanner ir = new Scanner(is);
         ir.useLocale(Locale.US);
         while (ir.hasNext()){
            double dest = ir.nextDouble();
            int lights = ir.nextInt();
            CycleProblem cp = new CycleProblem(dest, lights);

            for (int k = 0; k < lights; k++){
               double pos = ir.nextDouble();
               double red = ir.nextDouble();
               double green = ir.nextDouble();
               TrafficLight t = new TrafficLight(pos, red, green);
               cp. addLight(t);
            }
            double sol = cp.earliest();

            StringBuilder sb = new StringBuilder();
            Formatter formatter = new Formatter(sb, Locale.US);
            formatter.format("%3.3f\n", sol);
            System.out.print(formatter.toString());
        }
        is.close();
      }
      catch (IOException iox){}
   }
}

class CycleProblem {

   TrafficLight [] lights;
   int lightCount = 0;
   double dest;
   double arrival;

   public CycleProblem(double dest, int lIn){
      this.dest = dest;
      lights = new TrafficLight [lIn +1];
      addLight(new StartingLine());
   }

   public void addLight(TrafficLight tl){
      lights[lightCount++] = tl;
   }

    private boolean runsFreeFromTo(Traject tr, int n, int k){
       //check the lights past no n, before k, if it cuts the traject
       for (int t = n + 1; t < k; t++)
          if (lights[t].cuts(tr))
             return false;
       return true;
   }

   private void update (State start, State target, int fromLight, int toLight){
      Traject tr = start.trajectTo(target);
      if (tr != null && runsFreeFromTo(tr , fromLight, toLight))
         target.update(tr);
   }

   private void makeReachables(){
      for (int k = 1; k < lightCount; k++){
         for (State state: lights[k].makeReachables())
            for (int n = 0; n < k ; n++)
               for (State start : lights[n].getReachables()) // reachable from reachable state?
                  update(start, state, n, k);
         lights[k].cleanReachables(); // remove unreachable states
      }
   }

   public double earliest(){
      markBounds();
      makeReachables();
      findArrival();
      return arrival;
   }

   private void update(State st, int n){
       // update (when needed) arrival with the traject from st, which starts at light n
      Traject tr = st.traject();
      if (runsFreeFromTo(tr, n, lightCount)){
         double arr = tr.timeAt(dest);
         if (arr < arrival)
            arrival = arr;
      }
   }

   private void findArrival(){
      for (int n = 0; n < lightCount; n++)
         for (State start: lights[n].getReachables())
            update(start, n);
   }

   private void markBounds(){
      // bounds for the reachable states on a traffic light.
      Traject nonStop  = new Traject(0, 0, 0);// Ignore lights
      Traject stopping = new Traject(0, 0, 0);// legal trip. Stop for red light
      for (int k = 1; k < lightCount; k++){
         TrafficLight light = lights[k];
         double time = stopping.timeAt(light.position);
         if (light.isRed(time)){
             double greenTime = light.nextGreen(time);
             stopping = new Traject(greenTime, light.position, 0);
         }
      }

      double illegal = nonStop.timeAt(dest);
      arrival =  stopping.timeAt(dest); // first guess
      double gap = arrival - illegal;

      for (int k = 1; k < lightCount; k++){
         TrafficLight light = lights[k];
         light.lowerBound = nonStop.timeAt(light.position);
         light.upperBound = light.lowerBound + gap;
      }
   }
}

class Triple {
   static double AMAX = 0.5;
   double t,s,v;

   public Triple(double t, double s, double v){
      this.t = t;
      this.s = s;
      this.v = v;
   }
}

class State extends Triple{

   public State(double t, double s, double v){
      super(t, s, v);
   }

   public Traject traject(){
      return new Traject(t, s, v);
   }

   public Traject trajectTo(State target){
      double ds = target.s - this.s;
      double dt = target.t - this.t;
      if (dt <= 0)
         return null;
      Traject help = new Traject(0,0,0);
      double time = help.timeAt(ds);
      if (time <= dt)
         return new Traject(target.t - time, this.s, 0); // wait some time
      double vn = ds/dt - AMAX / 2 * dt;
      if (vn > v)
         return null; // can't leave here with that speed
      return new Traject(this.t, this.s,  vn);
   }

   public void update (Traject tr){
      State st = tr.stateAt(this.s);
      if(st.v > this.v)
         this.v = st.v;
   }
}

class Traject extends Triple{

   public Traject(double t, double s, double v){
      super(t, s, v);
   }

   State stateAt(double sIn){
      double ds = sIn - s;
      double dt = timeTo(ds);
      return new State(t + dt, sIn, v + AMAX * dt);
   }

   public double timeAt(double sIn){
      return t + timeTo(sIn - s);
   }

   private double timeTo(double ds){
      double D = v * v + 2 * AMAX * ds;
      return (- v + Math.sqrt(D)) / AMAX;
   }
}

class StartingLine extends TrafficLight{
    public StartingLine(){
       super(0,0,0);
       reachables.add(new State(0,0,0));
    }
}

class TrafficLight{
   double position;
   double redPeriod;
   double greenPeriod;
   double period;
   double lowerBound;
   double upperBound;

   ArrayList<State> reachables = new ArrayList<State>();

   public TrafficLight(double pos, double red, double green){
      position = pos;
      redPeriod = red;
      greenPeriod = green;
      period = green + red;
   }

   public ArrayList<State> getReachables(){
      return reachables;
   }

   public void cleanReachables(){
     // remove unreachable states
      for (int k = reachables.size() - 1; k >= 0; k--)
         if(reachables.get(k).v < 0)  // speed was not adjusted: unreachable
            reachables.remove(k);
   }

   public ArrayList<State> makeReachables(){
      // states that may be reachable (not sure) and are interesting
      double start = (int) (lowerBound/ period) * period;
      if (start < lowerBound){
         start+= redPeriod;
         reachables.add(new State(start, position, -10)); // speed will be adjusted when reachable
         start += greenPeriod;
      }
      while (start <= upperBound){
         reachables.add(new State(start, position, -10));
         start += redPeriod;
         if (start <= upperBound){
            reachables.add(new State(start, position, -10));
            start += greenPeriod;
         }
      }
      return reachables;
   }

   public boolean cuts(Traject tr){
      //does the orbit of tr pass this light when red?
      double time = tr.timeAt(position);
      return isRed(time);
   }

   public boolean isRed(double time){
      // is this light red at this time?
      int cycles = (int) (time / period);
      double rest = time - cycles * period;
      return rest < redPeriod;// ||rest == 0;
   }

   public double nextGreen(double time){
      if (isRed(time)){
         int cycles = (int)( time / period);
         return cycles * period + redPeriod;
      }
      else return time;
   }
}
