import {
  Component, OnInit, ElementRef, ViewChild, Input, Output,
  EventEmitter,
  HostListener,
  HostBinding
} from "@angular/core";
import {Goal} from "../../../../entities/goal";
import {Point} from "../../../../entities/point";

@Component({
  selector: "app-goal",
  templateUrl: "./goal.component.html",
  styleUrls: ["./goal.component.scss"]
})
export class GoalComponent implements OnInit {
  @Input() public goal: Goal;
  @Output() select = new EventEmitter<void>();

  position: Point;
  previousPosition: Point = new Point();

  hovered: boolean = false;

  constructor(private element: ElementRef) {
  }

  ngOnInit() {
    this.position = this.goal.position;
    this.position = new Point(300, 500);
  }

  @HostListener("mouseenter")
  onHover() {
    this.hovered = true;
  }

  @HostListener("mouseleave", ["$event"])
  onLeave(event) {
    this.hovered = false;
    if (this.dragging) {
      this.onMouseMove(event);
    }
  }

  private dragging = false;
  private offset: Point;

  @HostListener("mousedown", ["$event"])
  onMouseDown(event) {
    event.preventDefault();
    this.previousPosition.assign(this.position);
    this.offset = new Point(event.clientX - this.position.x, event.clientY - this.position.y);
    this.dragging = true;
  }

  @HostListener("mouseup", ["$event"])
  onMouseUp(event) {
    this.dragging = false;
  }

  @HostListener("mousemove", ["$event"])
  onMouseMove(event) {
    if (this.dragging) {
      this.position.x = event.clientX - this.offset.x;
      this.position.y = event.clientY - this.offset.y;
    }
  }

  @HostBinding("style.padding.px")
  get padding() {
    return this.hovered ? 10 : 2;
  }

  @HostBinding("style.margin")
  get margin() {
    return this.hovered ? "-8px 0 0 -8px" : "0";
  }

  @HostBinding("style.border-radius.%")
  get radius() {
    return this.hovered ? 0 : 50;
  }

  @HostBinding("style.left.px")
  get left() {
    return this.position.x;
  }

  @HostBinding("style.top.px")
  get top() {
    return this.position.y;
  }

  @HostListener("click", ["$event"])
  reposition(event) {
    if (this.previousPosition.equals(this.position)) this.select.emit();
  }

}
