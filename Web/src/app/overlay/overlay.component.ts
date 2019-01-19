import {Component, Output, EventEmitter, Input} from '@angular/core';
import {
  trigger,
  state,
  style,
  animate,
  transition,
  // ...
} from '@angular/animations';

@Component({
  selector: 'app-overlay',
  template: `<div [@openClose]="_displayed ? 'displayed' : 'hidden'" class="filler">
              <ng-content></ng-content>
            </div>`,
  styles: [`.filler { background-color: rgba(0, 0, 0, 0.9); }`],
  animations: [
    trigger("openClose", [
      state('hidden', style({
        'pointer-events': 'none',
        opacity: 0,
      })),
      state('displayed', style({
        'pointer-events': 'auto',
        opacity: 1,
      })),
      transition('hidden <=> displayed', [
        animate('.2s ease-out')
      ]),
    ]),
  ]
})
export class OverlayComponent {
  @Output('close') close = new EventEmitter<void>();

  private _displayed = false;
  inView = new EventEmitter<void>();

  @Input('displayed')
  set displayed(value: boolean) {
    this._displayed = value;
    this.inView.emit();
  }

  get displayed() {
    return this._displayed;
  }

  constructor() {
  }
}
