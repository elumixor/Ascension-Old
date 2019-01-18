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
  templateUrl: './overlay.component.html',
  styleUrls: ['./overlay.component.scss'],
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

  @Input() set displayed(value: boolean) {
    this._displayed = value;
    this.inView.emit();
  }

  constructor() {
  }
}
