import { TestBed, inject } from '@angular/core/testing';

import { ModulesControllerService } from './modules-controller.service';

describe('ModulesControllerService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [ModulesControllerService]
    });
  });

  it('should be created', inject([ModulesControllerService], (service: ModulesControllerService) => {
    expect(service).toBeTruthy();
  }));
});
