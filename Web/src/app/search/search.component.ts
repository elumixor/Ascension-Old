import {Component, HostListener, ElementRef, ViewChild, AfterViewInit} from '@angular/core';
import {OverlayComponent} from "../overlay/overlay.component";

@Component({
  selector: 'app-search',
  templateUrl: './search.component.html',
  styleUrls: ['./search.component.scss']
})
export class SearchComponent implements AfterViewInit {
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
