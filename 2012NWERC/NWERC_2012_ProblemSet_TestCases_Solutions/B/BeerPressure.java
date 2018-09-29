
// @EXPECTED_RESULTS@: CORRECT

import java.io.*;
import java.util.*;

public class BeerPressure {
   // private static final String infile = "beer.in";
   public static void main(String [] args){
      run();
   }

   public static void run(){
      InputStream is = null;

        // is = new FileInputStream(infile);
      is = System.in; // in case you want to read from System.in
      Scanner ir = new Scanner(is);
      while (ir.hasNext()){
        int dim = ir.nextInt();
        int total = ir.nextInt();
        int [] alfa = new int [dim];
        double [] score = new double [dim];
        int dSum = 0;
        for (int t = 0; t < dim; t++){
            int i = ir.nextInt();
            alfa[t] = i;
            dSum += i;
        }
        int rest = total - dSum;
        Bags bags = new Bags(dim, rest);

        for (int [] gamma : bags){
            double sol = solve(alfa, gamma);

            int [] beta = new int [dim];
            int max = 0;
            int count = 0;
            for (int t = 0; t < dim; t++){
                beta[t] = gamma[t] + alfa[t];
                if (max == beta[t])
                    count++;
                if (max < beta[t]){
                    max = beta[t];
                    count = 1;
                }
            }
            for (int t = 0; t < dim; t++)
                if (beta[t] == max)
                    score[t] += sol/count;
        }
        for (int t = 0; t < dim; t++){
            StringBuilder sb = new StringBuilder();
            Formatter formatter = new Formatter(sb, Locale.US);
            formatter.format("%2.2f", score[t] * 100);
            System.out.println("pub " + (t+1) + ": " + formatter.toString() + " %");
        }
    }
   }


    public static double solve (int [] k, int []x){
      int dim = x.length;

      int somX = 0;
      for (int t : x)
         somX += t;
      int somK = 0;
      for (int t : k)
         somK += t;
      IntSequence [] preTeller = new IntSequence[dim + 1];
      for (int t = 0; t < dim; t++)
         preTeller[t] = new Interval(k[t], x[t]);
      preTeller[dim] = new Interval(1, somX);
      IntSeqSeq teller = new IntSeqSeq(preTeller);

      IntSequence [] preNoemer = new IntSequence[dim+1];
      for (int t = 0; t < dim; t++)
         preNoemer[t] = new Interval(1,x[t]);
      preNoemer[dim] = new Interval(somK, somX);
      IntSeqSeq noemer = new IntSeqSeq(preNoemer);
      double result = 1;
       while (teller.hasNext() && noemer.hasNext()){
          if (result > 1)
             result /= noemer.next();
          else
             result *= teller.next();
      }
      while (teller.hasNext())
         result *= teller.next();
      while (noemer.hasNext())
             result /= noemer.next();
      return result;
   }

}

interface IntSequence{
   int next();
   boolean hasNext();
}

class Interval implements IntSequence{
   private int first;
   private int size;

   public Interval(int fIn, int sIn){
      first = fIn;
      size = sIn;
   }

   public int next(){
      int answer = first;
      first++;
      size--;
      return answer;
   }

   public boolean hasNext(){
      return size > 0;
   }

   public String toString(){
      return first + " " + size;
   }
}

class IntSeqSeq implements IntSequence{
   IntSequence[] parts;
   int present;

   public IntSeqSeq(IntSequence [] pIn){
      parts = pIn;
      present = 0;
      while (present < parts.length && !parts[present].hasNext())
         present++;
   }

   public boolean hasNext(){
      return present < parts.length;
   }

   public int next(){
      int answer = parts[present].next();
      while (present < parts.length && !parts[present].hasNext())
         present++;
      return answer;
   }

   public void dump(){
      for (IntSequence is : parts)
        System.out.println (" "+  is);
   }

}

class Bags implements Iterable <int []>,Iterator <int []>{
   private int [] next;
   private int dim;
   private int sum;


   public Bags(int m, int sum){
      dim = m;
      this.sum = sum;
      next = new int [dim];
      next[0] = sum;
   }

   public Iterator<int []> iterator(){
      return this;
   }

   public boolean hasNext(){
       return next != null;
   }

   public int [] next(){
      int [] answer = next.clone();
      setNext();
      return answer;
   }

   public void remove(){
       throw new UnsupportedOperationException("No remove in subsets");
    }

  void setNext(){
      if (sum == 0)
         next = null;
      else{
         int k = 0;
         while (next[k] == 0)
            k++;
         if (k == dim - 1)
            next = null;
         else{
           int rest = next[k];
           next[k] = 0;
           next[0] = rest - 1;
           next[k+1]++;
         }
      }
   }

}
