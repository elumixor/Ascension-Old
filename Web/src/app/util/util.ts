export function vh(v) {
  const h = Math.max(document.documentElement.clientHeight, window.innerHeight || 0);
  return (v * h) / 100;
}

export function vw(v) {
  const w = Math.max(document.documentElement.clientWidth, window.innerWidth || 0);
  return (v * w) / 100;
}

// export function abc() {
//   alert()
//
// }
