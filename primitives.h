
void triangle() {
	glBegin(GL_TRIANGLES);
	//front
	glColor3f(1.0f, 1.0f, 1.0f); //red
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	//right
	glColor3f(0.0f, 1.0f, 0.0f); //green
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	//back
	glColor3f(0.0f, 0.0f, 1.0f); //blue
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	//left
	glColor3f(1.0f, 1.0f, 0.0f); //yellow
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	//bottom
	glColor3f(1.0f, 0.0f, 0.0f); //cyan
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
}

//pyramid
void pyramid() {
	glBegin(GL_TRIANGLES);
	//front
	glColor3f(0.0f, 1.0f, 0.0f); //red
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	//right
	glColor3f(0.0f, 1.0f, 0.0f); //green
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	//back
	glColor3f(0.0f, 0.0f, 1.0f); //blue
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	//left
	glColor3f(1.0f, 1.0f, 0.0f); //yellow
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	//bottom
	glColor3f(1.0f, 0.0f, 0.0f); //cyan
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
}

//cube
void cube() {
	glBegin(GL_QUADS);
	//front
	//glColor3f(1.0f, 0.0f, 0.0f); //red
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//right
	//glColor3f(0.0f, 1.0f, 0.0f); //green
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	//back
	//glColor3f(0.0f, 0.0f, 1.0f); //blue
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//left
	//glColor3f(1.0f, 1.0f, 0.0f); //yellow
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.5f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//top
	//glColor3f(0.0f, 1.0f, 1.0f); //cyan
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.5f);
	glVertex3f(-1.0f, 1.0f, -1.5f);

	//bottom
	//glColor3f(0.0f, 0.0f, 0.0f); //black
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.5f);
	glVertex3f(-1.0f, -1.0f, -1.5f);
	glEnd();



}
