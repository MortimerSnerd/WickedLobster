// Quaternions.  Implementation largely borrowed from lobster geom.h.
import vec

struct quat:
   v: float3
   w: float

   // Return axis, rotation of quaternion.
   def decompose() -> float3, float:
      let vmag = magnitude(v)
      return v/vmag, 2.0*atan2(float2{vmag, w})

   def operator*(s: float) -> quat:
      return quat{v*s, w*s}

   def operator*(o: quat) -> quat:
      return quat{v*o.v, w*o.w}

   def operator-() -> quat:
      return quat{-v, w}
      
   def transform(p: float3) -> float3:
      return p + cross(v, cross(v, p) + p*w) * 2.0

   def normalize_q() -> quat:
      let mg = sqrt(dot(v, v) + w*w)
      return quat{v/mg, w/mg}

   def negated() -> quat:
      return quat{-v, w}

   def as_float4() -> float4:
      return float4{v.x,v.y,v.z,w}

def mk_quat(axis: float3, angle: float) -> quat:
   let cs = sincos(0.5 * angle)
   return quat{axis*cs[1], cs[0]}

def mk_quat(v: float4) -> quat:
   return quat{xyz(v), v.w}

// Return quat to rotate u to v.  Yanked directly from
// Lobster's geom.h.
def mk_quat_from_vectors(u: float3, v: float3) -> quat:
    let norm_u_norm_v = sqrt(dot(u, u) * dot(v, v))
    var real_part     = norm_u_norm_v + dot(u, v)
    var w = float3_0
    if real_part < 1.0e-6 * norm_u_norm_v:
        real_part = 0.0
        w = if abs(u.x) > abs(u.z): float3{-u.y, u.x, 0.0} else: float3{0.0, -u.z, u.y}
    else:
        w = cross(u, v)
    let q = quat{w, real_part}
    return q.normalize_q()
