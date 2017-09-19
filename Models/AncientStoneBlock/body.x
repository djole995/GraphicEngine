xof 0302txt 0064


// boid
Mesh boid {
 // vertices 
 7;                         // number of vertices
 0.00; 0.00; 0.50;,         // vertice 0
 0.50; 0.00;-0.50;,         // vertice 1
 0.15; 0.15;-0.35;,         // vertice 2
-0.15; 0.15;-0.35;,         // vertice 3
 0.15;-0.15;-0.35;, 
-0.15;-0.15;-0.35;,
-0.50; 0.00;-0.50;; 

 10;                         // number of triangles
 3;0,1,2;,                   // triangle #1
 3;0,2,3;,                   // triangle #2
 3;0,3,6;,                   // triangle #3
 3;0,4,1;,                   // ...
 3;0,5,4;,
 3;0,6,5;,
 3;1,4,2;,
 3;2,4,3;,
 3;3,4,5;,
 3;3,5,6;;


 MeshMaterialList {
  1;                         // one material
  10;                        // ten faces
  0,0;;                      // face #1 use material #0
  0,0;;                      // face #2 use material #0
  0,0;;                      // face #3 use material #0
  0,0;;                      // face #4 use material #0
  0,0;;                      // face #5 use material #0
  0,0;;                      // face #6 use material #0
  0,0;;                      // face #7 use material #0
  0,0;;                      // face #8 use material #0
  0,0;;                      // face #9 use material #0
  0,0;;                      // face #10 use material #0

  Material {                 // material #0
   1.0;0.92;0.0;1.0;;
   1.0;
   0.0;0.0;0.0;;
   0.0;0.0;0.0;;
  }

 MeshNormals {
  9;                       // 9 normals for every face
  0.2; 1.0; 0.0;,          // normal #1
  0.1; 1.0; 0.0;,          // normal #2
  0.0; 1.0; 0.0;,          // normal #3
 -0.1; 1.0; 0.0;,          // normal #4
 -0.2; 1.0; 0.0;,          // normal #5
 -0.4; 0.0;-1.0;,          // normal #6
 -0.2; 0.0;-1.0;,          // normal #7
  0.2; 0.0;-1.0;,          // normal #8
  0.4; 0.0;-1.0;;          // normal #9

  9;                       // 9 faces
  4;0,0,0;,                // connect face #1 with normal #1
  4;1,1,1;,                // connect face #2 with normal #2  
  4;2,2,2;,                // connect face #3 with normal #3
  4;3,3,3;,                // connect face #4 with normal #4
  4;4,4,4;,                // connect face #5 with normal #5
  4;5,5,5;,                // connect face #6 with normal #6
  4;6,6,6;,                // connect face #7 with normal #7
  4;7,7,7;,                // connect face #8 with normal #8
  4;8,8,8;;                // connect face #9 with normal #9
  }

  }
 }
}