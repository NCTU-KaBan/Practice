// @EXPECTED_RESULTS@: CORRECT

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class FoulPlay {
    protected int k, n, h;
    TreeMap<Integer,ArrayList<Integer>> M;
    // lhs: lose from 1
    // rhs: win from 1
    ArrayList<Integer> lhs;
    ArrayList<Integer> rhs;

    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner(System.in);
        int k=0;
        while(sc.hasNext())
        {
            ++k;
            //System.out.println("game " + k);
            FoulPlay w = new FoulPlay( sc );
            w.findGame();
        }
    }


    public FoulPlay( Scanner sc )
    {
        n = sc.nextInt();
        h = (int) Math.round(Math.log(n)/Math.log(2));
        M = new TreeMap<Integer,ArrayList<Integer>>();
        lhs = new ArrayList<Integer>();
        rhs = new ArrayList<Integer>();
        for( int i = 1; i <= n; ++i )
        {
            String s = sc.next();
            ArrayList<Integer> li = new ArrayList<Integer>();
            if( i == 1 )
                lhs = li;
            M.put(i, li);
            for( int j = 1; j <= n; ++j )
            {
                if(s.charAt(j-1) == '1')
                    li.add(j);
                else if(i==1 && j!=1) // 1 will lose from these
                    rhs.add(j);
            }
        }

    }

    public void findGame()
    {
        for( int l = 1; l <= h; ++l )
        {
            TreeMap<Integer,ArrayList<Integer>> cap = new TreeMap<Integer,ArrayList<Integer>>();
            TreeMap<Integer,Integer> flow = new TreeMap<Integer,Integer>();
            // cap is copy M, but only lhs -> rhs
            for( Map.Entry<Integer,ArrayList<Integer>> e : M.entrySet())
            {
                ArrayList<Integer> nb = new ArrayList<Integer>();
                Integer i = e.getKey();
                if( lhs.contains(i) )
                {
                    for( Integer j : e.getValue() )
                        if( rhs.contains(j) )
                           nb.add(j);
                    cap.put(e.getKey(), nb );
                }
            }
            // do the matching
            for( Integer i : lhs )
                match( i, cap, flow, new ArrayList<Integer>() );
            for( Map.Entry<Integer,Integer> e : flow.entrySet() )
            {
                Integer i = e.getKey();
                Integer j = e.getValue();
                if( lhs.contains(i) )
                    play( i, j );
            }
            // let 1 play against a remaining lhs
            Iterator<Integer> it = lhs.iterator();
            boolean success = false;
            Integer i = null;
            while( ! success && it.hasNext() )
            {
                i = it.next();
                success = ! flow.containsKey(i);
            }
            System.out.println( 1 + " " + i );
            Integer lostto1 = i;
            // collect remaining teams and let them play against each other
            ArrayList<Integer> remaining = new ArrayList<Integer>();
            for( Integer j : rhs )
            {
                remaining.add(j);
            }
            while( it.hasNext() )
            {
                i = it.next();
                if( ! flow.containsKey(i) )
                {
                    remaining.add(i);
                }

            }
            remove( lostto1 );
            for (it = remaining.iterator(); it.hasNext();)
            {
                Integer j1 = it.next();
                Integer j2 = it.next();
                play(j1, j2);
            }
        }
    }

    public void play( Integer j1, Integer j2 )
    {
        if( M.get(j1).contains(j2) )
        {
            System.out.println( j1 + " " + j2 );
            remove(j2);
        }
        else
        {
            System.out.println( j2 + " " + j1 );
            remove(j1);

        }
    }

    public void remove( Integer j )
    {
        // remove j from remaining game
        if( M.containsKey(j) )
            M.remove(j);
        for( ArrayList<Integer> li : M.values() )
            if( li.contains(j) )
                li.remove(j);
        if( lhs.contains(j) )
            lhs.remove(j);
        if( rhs.contains(j) )
            rhs.remove(j);
    }

    public boolean match( Integer i, TreeMap<Integer,ArrayList<Integer>> cap,
            TreeMap<Integer,Integer> flow, ArrayList<Integer> visited )
    {
        if( visited.contains(i) )
            return false;
        visited.add(i);
        Iterator<Integer> it = cap.get(i).iterator();
        boolean success = false;
        Integer j = null;
        while( ! success && it.hasNext() )
        {
            j = it.next();
            if( rhs.contains(j) )
            {
                success = true;
                rhs.remove(j); // once rhs is allocated, it stays
            } else
            {
                success = match( j, cap, flow, visited );
            }
        }
        if( success ) {
            flow.put(i,j);
            // overwrites if necessary

            // remove i->j from cap
            cap.get(i).remove(j);
            // add j->i to cap
            if( cap.containsKey(j) )
                cap.get(j).add(i);
            else
                cap.put(j, new ArrayList<Integer>(i));
        }
        return success;
    }

}
