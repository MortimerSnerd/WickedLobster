// Some partial matrix implementations, just enough to get
// whatever I need at hand. I'm definitely taking implementation
// from Lobster's geom.h wherever possible.  Keeping it simple by
// not trying to make it too generic, there's a lot of reuse that could
// be done at the cost of loops.
//
import core.quat

class mat3x3:
   col0: float3
   col1: float3
   col2: float3

   def row(i: int) -> float3:
      return float3{col0[i], col1[i], col2[i]}

   def transpose() -> mat3x3:
      let res = mat3x3{float3_0, float3_0, float3_0}
      res.col0 = row(0)
      res.col1 = row(1)
      res.col2 = row(2)
      return res

   def operator*(o: mat3x3) -> mat3x3:
      let t = transpose()
      let res = mat3x3{float3_0, float3_0, float3_0}
      res.col0 += float3_x*dot(t.col0, o.col0) 
      res.col0 += float3_y*dot(t.col1, o.col0)
      res.col0 += float3_z*dot(t.col2, o.col0)

      res.col1 += float3_x*dot(t.col0, o.col1) 
      res.col1 += float3_y*dot(t.col1, o.col1)
      res.col1 += float3_z*dot(t.col2, o.col1)

      res.col2 += float3_x*dot(t.col0, o.col2) 
      res.col2 += float3_y*dot(t.col1, o.col2)
      res.col2 += float3_z*dot(t.col2, o.col2)
      return res

   def operator*(v: float3) -> float3:
      var res = float3_0
      res += col0 * v.x
      res += col1 * v.y
      res += col2 * v.z
      return res

class mat4x4:
   col0: float4
   col1: float4
   col2: float4
   col3: float4

   def row(i: int) -> float4:
      return float4{col0[i], col1[i], col2[i], col3[i]}

   def transpose() -> mat4x4:
      let res = mat4x4{float4_0, float4_0, float4_0, float4_0}
      res.col0 = row(0)
      res.col1 = row(1)
      res.col2 = row(2)
      res.col3 = row(3)
      return res

   def operator*(o: mat4x4) -> mat4x4:
      let t = transpose()
      let res = mat4x4{float4_0, float4_0, float4_0, float4_0}
      res.col0 += float4_x*dot(t.col0, o.col0) 
      res.col0 += float4_y*dot(t.col1, o.col0)
      res.col0 += float4_z*dot(t.col2, o.col0)
      res.col0 += float4_w*dot(t.col3, o.col0)

      res.col1 += float4_x*dot(t.col0, o.col1) 
      res.col1 += float4_y*dot(t.col1, o.col1)
      res.col1 += float4_z*dot(t.col2, o.col1)
      res.col1 += float4_w*dot(t.col3, o.col1)

      res.col2 += float4_x*dot(t.col0, o.col2) 
      res.col2 += float4_y*dot(t.col1, o.col2)
      res.col2 += float4_z*dot(t.col2, o.col2)
      res.col2 += float4_w*dot(t.col3, o.col2)

      res.col3 += float4_x*dot(t.col0, o.col3) 
      res.col3 += float4_y*dot(t.col1, o.col3)
      res.col3 += float4_z*dot(t.col2, o.col3)
      res.col3 += float4_w*dot(t.col3, o.col3)

      return res

   def operator*(v: float4) -> float4:
      var res = float4_0
      res += col0 * v.x
      res += col1 * v.y
      res += col2 * v.z
      res += col3 * v.w
      return res


def mat4x4_identity():
    return mat4x4{float4_x, float4_y, float4_z, float4_w}

def mat4x4_translation(t: float3):
    return mat4x4{float4_x, float4_y, float4_z, vec4(t, 1.0)}

// Create from builtins that return matrices as 
// float arrays.
def mat4x4_from(arr: [float]) -> mat4x4:
   return mat4x4{
      float4{arr[0],  arr[1],  arr[2],  arr[3]},
      float4{arr[4],  arr[5],  arr[6],  arr[7]},
      float4{arr[8],  arr[9],  arr[10], arr[11]},
      float4{arr[12], arr[13], arr[14], arr[15]}}
      

class mat4x3:
   col0: float3
   col1: float3
   col2: float3
   col3: float3

   def operator*(v: float4) -> float3:
      var res = float3_0
      res += col0 * v.x
      res += col1 * v.y
      res += col2 * v.z
      res += col3 * v.w
      return res

class mat3x4:
   col0: float4
   col1: float4
   col2: float4

   def row(i: int) -> float3:
      return float3{col0[i], col1[i], col2[i]}

   def transpose() -> mat4x3:
      let res = mat4x3{float3_0, float3_0, float3_0, float3_0}
      res.col0 = row(0)
      res.col1 = row(1)
      res.col2 = row(2)
      res.col3 = row(3)
      return res

   def operator*(o: mat3x4) -> mat3x4:
      return mat3x4{
         o.col0*col0.x + o.col1*col0.y + o.col2*col0.z + float4{0.0, 0.0, 0.0, col0.w},
         o.col0*col1.x + o.col1*col1.y + o.col2*col1.z + float4{0.0, 0.0, 0.0, col1.w},
         o.col0*col2.x + o.col1*col2.y + o.col2*col2.z + float4{0.0, 0.0, 0.0, col2.w}}

   def operator*(v: float3) -> float4:
      var res = float4_0
      res += col0 * v.x
      res += col1 * v.y
      res += col2 * v.z
      return res

   // Calculate v * this
   def pre_mult(v: float4) -> float3:
      var res = float3_0
      res += row(0) * v.x
      res += row(1) * v.y
      res += row(2) * v.z
      res += row(3) * v.w
      return res

def mat3x4_from_3x3(o: mat3x3, trans = float3_0):
    return mat3x4{
      vec4(o.col0, trans.x),
      vec4(o.col1, trans.y),
      vec4(o.col2, trans.z)}


//TODO These two need a better place since it is specific to iqm 
def iqm_rotation_scale_trans(q: quat, scale: float3, trans: float3) -> mat3x4:
   let m = rotation_3x3(q)
   m.col0 *= scale
   m.col1 *= scale
   m.col2 *= scale
   //MEMO trans works as a row in 3x4 because it is pre-multiplied for iqm calcs.
   return mat3x4_from_3x3(m, trans)

def iqm_invertortho(o: mat3x4) -> mat3x4:
   let inv = o.transpose()
   inv.col0 /= mag_squared(inv.col0)
   inv.col1 /= mag_squared(inv.col1)
   inv.col2 /= mag_squared(inv.col2)
   return mat3x4{
      vec4(inv.col0, -dot(inv.col0, inv.col3)),
      vec4(inv.col1, -dot(inv.col1, inv.col3)), 
      vec4(inv.col2, -dot(inv.col2, inv.col3))}

def rotation_3x3(q: quat) -> mat3x3:
   let x = q.v.x
   let y = q.v.y
   let z = q.v.z
   let w = q.w
   let tx = 2.0*x
   let ty = 2.0*y
   let tz = 2.0*z
   let txx = tx*x
   let tyy = ty*y
   let tzz = tz*z
   let txy = tx*y
   let txz = tx*z
   let tyz = ty*z
   let twx = w*tx
   let twy = w*ty
   let twz = w*tz
   return mat3x3{
      float3{1.0 - (tyy + tzz), txy - twz, txz + twy}, 
      float3{txy + twz, 1.0 - (txx + tzz), tyz - twx},
      float3{txz - twy, tyz + twx, 1.0 - (txx + tyy)}}

def rotation_3x3(axis: float3, angle: float) -> mat3x3:
   let q = mk_quat(axis, angle)
   return rotation_3x3(q)

def rotation_3x4(axis: float3, angle: float) -> mat3x4:
   let m = rotation_3x3(axis, angle)
   return mat3x4_from_3x3(m)

def rotation_4x4(axis: float3, angle: float) -> mat4x4:
    let m = rotation_3x3(axis, angle)
    return mat4x4{vec4(m.col0, 0.0), vec4(m.col1, 0.0), vec4(m.col2, 0.0), float4_w}

def mat3x4_identity():
    return mat3x4{float4_x, float4_y, float4_z}
