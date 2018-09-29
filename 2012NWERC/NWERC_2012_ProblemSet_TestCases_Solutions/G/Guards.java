// @EXPECTED_RESULTS@: CORRECT

import java.util.*;

public class Guards {
    protected TreeMap<Integer,TreeSet<Integer>> edges;
    protected TreeMap<Integer,ArrayList<Wing>> children; // key is child's connection
    protected int minCoverIn; // connection is included in cover, but don't count
    protected int minCoverOut; // connection not included in cover
    protected Integer connection;
    protected int k;
    protected int n,m,c;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int i=0;
        while(sc.hasNext())
        {
            ++i;
            Wing w = new Wing( i, sc );
            w.ComputeVertexCovers();
            System.out.println(w.getMinCoverOut());
        }
    }

    public Wing( int l, Scanner sc )
    {
        this( l, sc, -1 );
    }

    public Wing( int l, Scanner sc, int connect)
    {
        connection = new Integer(connect);
        k = l;
        n = sc.nextInt();
        m = sc.nextInt();
        c = sc.nextInt();
        edges = new TreeMap<Integer,TreeSet<Integer>>();
        children = new TreeMap<Integer,ArrayList<Wing>>();
        for( int j = 1; j <= m; ++j )
        {
            insertEdge(sc.nextInt(), sc.nextInt());
        }
        for( int j = 1; j <= c; ++j )
        {
            int child_connect = sc.nextInt();
            int child_connect2 = sc.nextInt();
            Wing w = new Wing(k, sc, child_connect);
            w.insertEdge( child_connect, child_connect2 );
            if( children.containsKey(child_connect) )
                children.get(child_connect).add(w);
            else
            {
                ArrayList<Wing> ts = new ArrayList<Wing>();
                ts.add(w);
                children.put(child_connect, ts );
            }
        }

    }

    public void print()
    {
        System.out.println(n + " " + m + " " + c);
        for( Map.Entry<Integer,TreeSet<Integer>> e : edges.entrySet() )
        {
            for( Integer j : e.getValue() ) {
               System.out.println(e.getKey() + " " + j );
            }
        }

        for( Map.Entry<Integer, ArrayList<Wing>> e : children.entrySet() )
        {
            for( Wing w : e.getValue() )
            {
                w.print();
            }
        }
    }

    final protected void insertEdge( int u, int v )
    {
        if( ! edges.containsKey(u) )
            edges.put(u, new TreeSet<Integer>() );
        edges.get(u).add(v);
    }

    public void ComputeVertexCovers()
    {
        for( Map.Entry<Integer, ArrayList<Wing>> e : children.entrySet() )
        {
            for( Wing c : e.getValue() )
            {
                c.ComputeVertexCovers();
            }
        }

        TreeMap<Integer,TreeSet<Integer>> copyEdges = new TreeMap<Integer,TreeSet<Integer>>();
        for( Map.Entry<Integer,TreeSet<Integer>> e : edges.entrySet() )
        {
            copyEdges.put( e.getKey(), new TreeSet<Integer>(e.getValue()));
        }

        minCoverIn = selectInCover( edges, connection ) - 1;
        minCoverIn += getMinCover( edges );


        minCoverOut = 0;
        TreeSet<Integer> neighbors = new TreeSet<Integer>();
        if(copyEdges.containsKey(connection))
            for( Integer n : copyEdges.get(connection) )
                neighbors.add(n);
        for( Map.Entry<Integer,TreeSet<Integer>> e : copyEdges.entrySet() )
        {
            if( e.getValue().contains(connection))
                neighbors.add( e.getKey() );
        }

        for( Integer n : neighbors )
            minCoverOut = selectInCover( copyEdges, n );
        minCoverOut += getMinCover( copyEdges );


        assert( minCoverIn <= minCoverOut );
    }

    protected int selectInCover( TreeMap<Integer,TreeSet<Integer>> remainingEdges,
            Integer w )
    {
        assert( w != null && w.intValue() != -1);
        int value = 1;

        // add children of w
        if( children.containsKey(w))
            for( Wing c : children.get(w) )
            {
                value += c.getMinCoverIn();
            }

        // if neighbors of w have no other edges
        if( remainingEdges.containsKey(w))
        for( Integer i : remainingEdges.get(w) )
        {
            if( ! remainingEdges.containsKey(i) )
            {
                boolean isolated = true;
                for( Map.Entry<Integer,TreeSet<Integer>> e : remainingEdges.entrySet())
                {
                    if( ! e.getKey().equals(w) &&
                        e.getValue().contains(i) )
                    {
                        isolated = false;
                        break;
                    }
                }
                if( isolated && children.containsKey(i))
                    for( Wing c : children.get(i) )
                        value += c.getMinCoverOut();
            }
        }
        remainingEdges.remove(w);

        LinkedList<Integer> toRemove = new LinkedList<Integer>();
        for( Map.Entry<Integer,TreeSet<Integer>> e : remainingEdges.entrySet())
        {
            if( e.getValue().remove(w) )
                if( e.getValue().isEmpty() )
                    toRemove.add(e.getKey());
        }
        for( Integer i : toRemove )
        {
            remainingEdges.remove(i);
            boolean isolated = true;
            for( Map.Entry<Integer,TreeSet<Integer>> e : remainingEdges.entrySet())
            {
                if( e.getValue().contains(i) )
                {
                    isolated = false;
                    break;
                }
            }
            if( isolated && children.containsKey(i))
                for( Wing c : children.get(i) )
                {
                    value += c.getMinCoverOut();
                }
        }
        return value;
    }


    protected int getMinCover( TreeMap<Integer,TreeSet<Integer>> remainingEdges )
    {
        if( remainingEdges.isEmpty() )
        {
            return 0;
        }
        else
        {
            // select an edge (u,v)
            Integer u = remainingEdges.keySet().iterator().next();
            Integer v = remainingEdges.get(u).first();
            // do two recursive calls:
            TreeMap<Integer,TreeSet<Integer>> uEdges = new TreeMap<Integer,TreeSet<Integer>>();
            TreeMap<Integer,TreeSet<Integer>> vEdges = new TreeMap<Integer,TreeSet<Integer>>();
            for( Map.Entry<Integer,TreeSet<Integer>> e : remainingEdges.entrySet() )
            {
                uEdges.put( e.getKey(), new TreeSet<Integer>(e.getValue()));
                vEdges.put( e.getKey(), new TreeSet<Integer>(e.getValue()));
            }


            int u_value = selectInCover( uEdges, u);
            u_value += getMinCover( uEdges );

            int v_value = selectInCover( vEdges, v);
            v_value += getMinCover( vEdges );

            return Math.min(u_value, v_value);
        }
    }

    public int getMinCoverIn()
    {
        return minCoverIn;
    }

    public int getMinCoverOut()
    {
        return minCoverOut;
    }

}
