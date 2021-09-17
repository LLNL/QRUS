
void diffuse_step(
  float D, float dt, float dx2, float dy2,
  const unsigned N, const unsigned M,
  float * V, float const * U
) {
  float coef1 = ( D * dt ) / ( dx2 * dy2 );
  float coef2 = 2.f * ( 1.f + ( D * dt ) * ( 1.f / dy2 + 1.f / dx2 ) );

  for (int i = 1; i < N-1; i++) {
    for (int j = 1; j < M-1; j++) {
      V[i*M+j] = coef1 * (
                            dy2 * ( U[ (i+1) * M + j ] + U[ (i-1) * M + j ] ) +
                            dx2 * ( U[ i * M + (j-1) ] + U[ i * M + (j+1) ] )
                 ) - coef2 * U[i*M+j];
    }
  }
}

