/**
 * Point class represents position in base coordinates: (-1, -1) to (1, 1)
 * Point(0, 0) would represent a point in the center of coordinate system
 *
 * By using ``trasnform(...)`` you can transform point's coordinates to a new square
 */
export class Point {
  x: number;
  y: number;

  constructor(xOrBoth?: number = 0, y?: number) {
    this.x = xOrBoth;
    this.y = y == null ? this.x : y;
  }

  /**
   * Assigns value
   * @param {Point} that
   */
  assign(that: Point): void {
    this.x = that.x;
    this.y = that.y;
  }

  /**
   * Check for equality
   * @param {Point} that
   * @return {boolean}
   */
  equals(that: Point): boolean {
    return this.x === that.x && this.y === that.y;
  }

  /**
   * Create a transformation function from base coordinates to a square
   * @return {(Point) => Point}
   * @param lb
   * @param rt
   */
  static transformTo(lb: Point, rt: Point): (Point) => Point {
    const minX = lb.x;
    const maxX = rt.x - lb.x;

    const minY = lb.y;
    const maxY = rt.y - lb.y;

    const inter1X = maxX / 2;
    const inter2X = inter1X + minX;

    const inter1Y = maxY / 2;
    const inter2Y = inter1Y + minY;

    return (p: Point): Point => new Point(p.x * inter1X + inter2X, p.y * inter1Y + inter2Y);
  }

  /**
   * Transforms from square coordinates to base coordinates
   * @param {Point} lb
   * @param {Point} rt
   * @return {(Point) => Point}
   */
  static transformFrom(lb: Point, rt: Point): (Point) => Point {
    const minX = lb.x;
    const maxX = rt.x - lb.x;

    const minY = lb.y;
    const maxY = rt.y - lb.y;

    const inter1X = 2 / maxX;
    const inter2X = inter1X * minX + 1;

    const inter1Y = 2 / maxY;
    const inter2Y = -1 * (inter1Y * minY + 1);

    return (p: Point): Point => new Point(p.x * inter1X + inter2X, p.y * inter1Y + inter2Y);
  };
}
