#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif
attribute vec3 aVertexPosition;
  attribute vec4 aVertexColor;

  uniform mat4 mvp_matrix;
//  uniform mat4 uPMatrix;

  varying vec4 vColor;

  void main(void) {
//	gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
	gl_Position = mvp_matrix * vec4(aVertexPosition, 1.0);
	vColor = aVertexColor;
  }
