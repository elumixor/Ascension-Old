import {Component, HostListener, ElementRef, ViewChild, AfterViewInit} from '@angular/core';
import {OverlayComponent} from "../overlay.component";

@Component({
  selector: 'app-search-overlay',
  template: `<input type="text" placeholder="Search" #input>`,
  styleUrls: ['./search-overlay.component.scss']
})
export class SearchOverlayComponent implements AfterViewInit {
  @ViewChild("input") input: ElementRef;

  constructor(private overlay: OverlayComponent) {
    overlay.inView.subscribe(() => {
      this.input.nativeElement.focus();
    });
  }

  ngAfterViewInit() {
    this.input.nativeElement.focus();
  }

  @HostListener('document:keydown', ['$event'])
  hideSearch(event: KeyboardEvent) {
    if (event.code === "Escape") {
      this.overlay.close.emit();
    }
  }
}
