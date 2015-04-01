
#ifndef EPSILON
#define EPSILON 0.00001f

Plane::Plane()
{

}

double Plane::intersects(Ray ray, QMatrix4x4 transform)
{
	/**
	 * We use the formulas available from Shirley pg 78
	 * in which the plane is defined by three points of
	 * a triangle. 
	 * This is simply for expedience in completing the 
	 * assignment now, many optimizations may be made 
	 * this at a later time. 
	 */

	 //Base plase is on the ground, and is a metre square.
	 QVector3D a, b, c;
	 ap = transform * QVector3D(0.5, 0, 0.5);
	 bp = transform * QVector3D(0.5, 0, -0.5);
	 cp = transform * QVector3D(-0.5, 0, -0.5);

	 double B, Y, t, M;
	 double a,b,c,d,e,f,g,h,i,j,k,l;
	 double ei_hf, gf_di, dh_eg, ak_jb, jc_al, bl_kc, 

	 a = ap.x() - bp.x();
	 b = ap.y() - bp.y();
	 c = ap.z() - bp.z();
	 d = ap.x() - cp.x();
	 e = ap.y() - cp.y();
	 f = ap.z() - cp.z();
	 g = ray.direction.x();
	 h = ray.direction.y();
	 i = ray.direction.z();
	 j = ap.x() - ray.origin.x();
	 k = ap.y() - ray.origin.y();
	 l = ap.z() - ray.origin.z();

	 ei_hf = e*i-h*f;
	 gf_di = g*f-d*i;
	 dh_eg = d*h-e*g;
	 ak_jb = a*k-j*b;
	 jc_al = j*c-a*l;
	 bl_kc = b*l-k*c;

	 M = a*ei_hf + b*gf_di + c*dh_eg;
	 if (fabs(M) < EPSILON)
	 {
	 	return -1;
	 } 
	 else
	 {
		 t = f*ak_jb + e*jc_al + d*bl_kc;
		 t = (-t / M) - EPSILON; //We nudge it back just a tad to ensure we get the correct
		 						 //Normal what it us used for that.
	 }

	 /*
	 B = j*ei_hf + k*gf_di + l*dh_eg;
	 B = B / M;
	 Y = i*ak_jb + e*jc_al + d*bl_kc;
	 Y = Y / M;
	 */

}

QVector3D getNormal(QVector3D p, QMatrix4x4 transform)
{

}

#endif