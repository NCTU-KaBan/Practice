
// @EXPECTED_RESULTS@: CORRECT

import java.util.*;
import java.io.*;

public class HipToBeSquare{

    public static void main (String [] args){
       run();
    }

    public static void run(){
      InputStream is = null;
      try{
         is = System.in;
         Scanner ir = new Scanner(is);
         while (ir.hasNext()){
            int a = ir.nextInt();
            int b = ir.nextInt();
            SquareSet sSet = new SquareSet(a,b);
            Num sol = sSet.minRoot();
            if (sol == null)
               System.out.println("none");
            else
               System.out.println(sol.root);
        }
        is.close();
      }
      catch (IOException iox){}
   }
}

class SquareSet{
   private static int PRIMES = 1300;
   private static int [] prime = new int [PRIMES];
   static {
      prime[0] = 2;
      int count = 0;
      for (int n = 3; count < PRIMES-1; n+=2){
         int k = 0;
         int p = prime[k];
         while (n % p != 0 && p * p <= n){
            k++;
            p = prime[k];
         }
         if (n % p != 0)
            prime[++count] = n;
      }
   }

   private TreeSet<Integer> pr = new TreeSet<Integer>();
   private TreeSet<Integer> set;

   private int max = 0, min = Integer.MAX_VALUE;
   TreeSet<Num>  numQueue;
   ArrayList<Num>  numSet;

   public SquareSet(int a, int b){
       // first optimization
       int preq = (int) Math.sqrt(a - 0.5);
       int q = preq + 1;
       if (q * q < b)
          b = q * q;
       set = new TreeSet<Integer> ();
       for (int k = a; k <= b; k++)
          set.add(k);
       min = a;
       max = b;
   }

   public Num minRoot(){
      reduce();
      mkQueue();
      Num champ = getChamp();
      return champ;
   }

   private Num getChamp(){
      while (! numQueue.isEmpty()){
         ArrayList<Num> extra = new ArrayList<Num>();
         Num num = numQueue.pollFirst();
         long sqf = num.sqf;
         if (sqf == 1)
            return (num);
         int ip = 0;
         while ( sqf % prime[ip] > 0)
           ip++;
         int p = prime[ip];
         for (Num num2 : numSet)
            if ((num.mask & num2.mask) == 0 && num2.sqf % p == 0 ){
                Num e = num2.times(num);
                if (e != null && e.isSmall())
                   extra.add(e);
            }
         numQueue.addAll(extra);
       }
      return null;
   }

   private void mkQueue(){
       numQueue = new TreeSet<Num>();
       numSet = new ArrayList<Num>(set.size());
       long mask = 1;
       int k = 0;
       for (int n : set){
          Num num = new Num(n);
          num.mask = mask;
          mask *= 2;
          numSet.add(num);
       }
       reduce2();
       numQueue.addAll(numSet);
   }

   private void reduce(){
       // remove all elements divisible by a prime that divides no other element
       // collect active primes
      int pp = 2;
      for (int ip = 0; ip < PRIMES && pp <= max; ip++){
         pp = prime[ip];
         pr.add(pp);
      }
      boolean done = false;
      while (!done){
         done = true;
         ArrayList<Integer> rem = new ArrayList<Integer>();
         for (int p : pr){
            int count = 0;
            int mult = 0;
            for (int nIn : set){
               int n = nIn;
               int exp = 0;
               while (n % p == 0){
                  n /= p;
                  exp++;
               }
               if (exp % 2 == 1){
                  count++;
                  mult = nIn;
               }
            }
            if (count == 1){
               set.remove(mult);
               done = false;
            }
            if (count <= 1)
               rem.add(p);
         }
         for (int m : rem)
            pr.remove(m);
      }
   }
    private void reduce2(){
       // pair all elements divisible by a prime that divides 2 elements
      boolean done = false;
      while (!done){
         done = true;
         for (int p : pr){
            int count = 0;
            Num [] mult = new Num[2];
            for (Num nIn : numSet){
               if (nIn.sqf % p == 0){
                  if (count < 2)
                     mult[count] = nIn;
                  count++;
               }
            }
            if (count == 2){
               if(mult[0].maal(mult[1]));
                   numSet.remove(mult[1]);
               done = false;
            }
         }
      }
   }
}

class Num implements  Comparable<Num>{
    // represent the number n as root * root * sqf where sqf is square-free
   long root, sqf;
   long mask;
   int size;

   List<Integer> primes;

   public Num(){
   }

   public Num (long n){
      sqf = n;
      root = 1;
      size = 1;
      primes = new ArrayList<Integer>();
      clean();
   }

   public Num times (Num that){
      if ((this.mask & that.mask) > 0)
         return null;
      Num result = new Num();
      long nroot = this.root * that.root;
      long sqf1 = this.sqf;
      long sqf2 = that.sqf;
      long eroot = 1;

      for (int p : primes){
         if (sqf2 % p == 0){
            eroot *= p;
            sqf1 /= p ;
            sqf2 /= p;
         }
      }
      result.root = nroot * eroot;
      result.sqf = sqf1 * sqf2;
      result.size = this.size + that.size;
      result.mask = this.mask | that.mask;
      return result;
   }

   public boolean maal(Num that){
      if ((this.mask & that.mask) > 0)
         return false;
      long nroot = this.root * that.root;
      long eroot = 1;
      long sqf1 = this.sqf;
      long sqf2 = that.sqf;
      for (int p : primes){
         if (sqf2 % p == 0){
            eroot *= p;
            sqf1 /= p ;
            sqf2 /= p;
         }
      }
      root = nroot * eroot;
      sqf = sqf1 * sqf2;
      size = this.size + that.size;
      mask = this.mask | that.mask;
      primes = new ArrayList<Integer>();
      for (int p = 2; p <= sqf; p++)
         if (sqf % p == 0)
            primes.add(p);
      return true;
   }

   private void clean(){
      for (int p = 2; (p * p) <= sqf; p++){
         while (sqf % (p*p) == 0){
            root *= p;
            sqf /= p * p;
         }
      }
      for (int p = 2; p <= sqf; p++)
         if (sqf % p == 0)
            primes.add(p);
   }

   public boolean isSmall(){
      return 1.01 *  root * sqf < Long.MAX_VALUE;
   }

   public int compareTo(Num other){
      if (this.equals(other))
         return 0;
      if (this.size != other.size)
         return this.size - other.size;
      if (this.sqf < other.sqf)
          return -1;
      if (this.sqf > other.sqf)
         return 1;
      if (this.root < other.root)
          return -1;
      if (this.root > other.root)
         return 1;
      return 0;
   }

   public boolean equals(Object other){
      if (other instanceof Num)
         return mask == ((Num) other).mask;
      return false;
   }
}
