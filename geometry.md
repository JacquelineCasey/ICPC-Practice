
# Semi-Detailed Computational Geometry Notes

Example problems:
- Closest Pair of Points
- Most distant pair of points
- Is a point in a polygon
- Line segment intersection
  - Harder: find all intersections.

4 techniques:
- cross product
- convex hull
- rotating calipers
- sweep line


## Technique 1: Cross Product

Two vectors, `(x1, y1), (x2, y2)`. Cross product is `x1*y2 - x2*y1`.
(Technically only defined in 3 dimensions, but this is enough for us)

If there is some `theta` between the vectors, this is equal to `|v_1|*|v_2|*sin(theta)`.

A common idea - sort vectors by angle with the x-axis.
- Calculating the angle is a pain, so instead we will sort based on the cross product.

There is a right hand rule. Fingers to v1, then curl to v2. If your thumb points at you,
its positive. (Convex ~ positive. Concave ~ negative).

### Example - Sorting Vectors by Angle

You have a set of points, `(x_i, y_i)` and `y_i > 0`. Goal: sort by angle to x-axis.

Supply a comparison function to `sort()`. Use the cross product of `v_1, v_2`. If
positive, `v_1` has a lower theta.

*Why not just use the angle*: Floating point precision is a pain in the ass. Avoid
floats wherever possible, even here. We will often only get integer coordinates,
so take advantage of this.

### Example - Line Segment Intersection

You get 2 segments (pairs of end points). `(v1, v2)` and `(v3, v4)` are the segments.
Decide whether they intersect.

Write the linear equation representing the line (not just the segment). Solve this
system of equations. Check if the intersection lies between the endpoints for both
segments.

This method has some problems however. Quite complicated, and it uses divisions (so
we end up back in floating point, or doing something silly with rationals). 

The cross product saves us again. Each line splits the plain in half. For each segment,
the two points should be on a different sides relative to the other segment. This is equivalent
to intersecting.

We require that `(v2 - v1) * (v3 - v1)`  and `(v2 - v1) * (v4 - v1)` have different
signs. This means `v3` and `v4` are on different sides.

We also need to check that the `v1, v2` segment are on different sides of `v3, v4`. This is similar.
If both checks succeed, we have intersecting lines.

This method is fairly simple, and it keeps everything on integers.

There is a downside: we don't have the location of the intersection. For this, we
fall back to the system of equations.

### Example - Sorting Vectors by Angle (part 2)

We remove the condition that `y` is positive. How do we sort the vectors now?

Why does the old solution not work? The cross product won't always work. We can have
vectors with negative cross product that are in the wrong order.

One Solution - (conceptually) divide vectors in two (positive y or negative y). 
The comparison function first determines if the vectors are in different sets. If so,
the positive y vector goes first. (Be aware of y=0 cases here. You will have to use x. The sets 
are actually `{0 <= theta < pi}` and `{pi <= theta < 2*pi`})

Some good news - you won't have to do this too often actually.


## Technique 2: Convex Hull

What is convex? A set (of points) in a euclidean space is convex iff for every segment whose
endpoints are in the the set, the entire segment is contained in the set.

(The interior of) circles, triangles, squares are convex. A star or the star trek shape
are not convex. You can draw a segment with endpoints that have parts outside the shape.

The convex hull of a set of points is the smallest convex st that contains the points.

(It is a polygon of some of the points. Observe that the interior angles are smaller than pi).

Both algorithms are `O(n log n)`. The sorting part of each will dominate. This is optimal, you can
reduce convex hull to sorting.

### How to Compute the Convex Hull - Graham Scan

Take the smallest y-coordinate point `v_0` (Break tie with smallest x). Sort points by 
angle with the x axis (with that lowest point acting as the origin). (Specifically, its the angle
`v_i` - `v_0` vs the `x` axis. Use the cross product. The tie breaker puts the closer vector to go first).

Maintain a set `H` (for hull). `H = {v_0}`.

For each `v_i` in sorted list:
- consider `H = {..., w_k-1, w_k}`.
- consider `(w_k - w_k-1) * (v_i - w_k)`.
  - If this is positive, we add `v_i` to `H`.
  - If this is negative or `0`, we remove `w_k` from `H`. You need to repeatedly pop until we have have a positive cross product (or this list has size 1).

(Really, a while loop cleans this up more. PS: There is a good visualization on wikipedia).

As a side note, thinking of the list as a stack is a good idea.

### How to Compute the Convex Hull - Monotone Chain

Choose whichever is more convenient. Most do Graham Scan.

Sort the points by x coordinate (tiebreaker should be consistent (increasing y)). Choose the leftmost point and rightmost point.

Construct the upper and lower convex hull seperately.

We call `v_0` be the first element (leftmost) and `v_n` be the last element `rightmost`.

Now we do two Graham scans, one for the top and one for the bottom. 

You should do `v_0 to v_n` convex for upper, and then do `v_0 to v_n` concave for lower.

Merge these two lists, be careful about `v_0, v_n`.

This is probably more complicated. I think I prefer Graham scan, right? One nice thing 
about Graham scan is that it is already sorted, there is no inversing. The major downside 
is the presort by angle step of Graham scan, which can be skipped in Monotone Chain (instead you sort by x).


## Technique 3: Rotating Callipers

This is a paradigm more than an algorithm. It depends on Convex Hull.

This is `O(n)` on its own, but you may need to call Convex Hull (`O(n log n)`). Note that you need
the hull to be sorted counterclockwise. (I mean clockwise works too probably, but you may need some
small changes).

### Example - Most Distant Pair of Points

Compute the convex hull. You take two imaginary parallel lines on the outside and
rotate them around the shape (conceptually). 

For any given set of two lines, there are two (ish, except for sparse cases) antipodal point.
We need only check all pairs of antipodal points.

On the convex hull:
Take the smallest y-coord point `v_1` (tie break with smallest-x), and take the largest
y-coord point `v_2`. These are antipodal.

Check the next point on the hull.

Compute the cross product of `(next_1 - v_1) * (v_2 - next_2)`. 
Positive means change `v_2`. Negative means change `v_1`. This gives a new pair of 
antipodal points.

There are `n` sets of antipodes, so you can stop after that. Or you can just wait until `v_2, v_1` is repeated.

### Example - Given 2 Convex Polygons, Find the Closest Two Points.

This time, one calliper is on the first polygon, and one is on the second polygon. Rotate them
together, and consider each pair of points.

You will get the closest distance between two vertices, which is nice. 

If you actually need closest point between to polygons, you need to consider vertex to
edge as well (and edge edge?). Which you can do as you advance on the the calliper points.


## Technique 4: Sweep Line

Also a paradigm rather than an algorithm.

This might also be called Line Sweep or Plane Sweep.

### Example - Closet Pair of Points

(There is a nice divide and conquer algorithm that barely has any geometry. I am 
prepared to give it if we need it - I really like that algorithm.)

Here is the sweep line algorithm.

Sort the points by `x` and maintain some `d = infinity`. This will eventually be the answer.

Maintain an ordered set `S = {}`, which we will order by `y`. (Recall that `C++'s` `std::set` is sorted. Also, `std::lower_bound` exists and returns an iterator.)

Check all points `d` close to `x` within that sorted list.

For each point `p = (x, y)`:
- Remove points from `S` with `x-coord` less than `x - d`.
- Check every pair `(p, q)` where `q` has `y-coord` in `[y-d, y+d]`. This needs to be `log n`.
  - Proof trick: there are only constant number of points in this lil rectangle (6 or 7). Geometry demands it.
- Update `d` accordingly.
- Add `p` to `S`.

### Example - Many Line Segment Intersections

Find all intersections.

If we know that there will be O(n) intersections, we can do better than brute force.

(This problem is output sensitive. If there are O(n^2) intersections, then we are
stuck with O(n^2) brute force).

Idea - move an imaginary vertical line from left to right. Everytime we move, it
will intersect some segments. The top to bottom order of segments will swap every
time two segments swap. 

Let the imaginary consider every `x` in all endpoints in the input.

We need to update the intersection order info:
- meet a new segment means add to the line.
- exit a segment means remove it from the line.

We will use a queue to manage events. Add and delete new line are easy.
On insert or delete of segment, we consider the new adjacent pairs to find when (if)
they intersect. We add that to the queue as well.

The runtime is something like `O((n + m) log (n + m))` where there are `m` intersections.

(And we ran out of time at this point.)


## Final Thoughts

- Be familiar with the cross product. It is awesome.
- Avoid floats whenever possible. (Also prefer `long` to `int`).
  - (Length can be proxied by computing it without the square root).

