import { ComponentFixture, TestBed } from '@angular/core/testing';

import { tabElectreIIIComponent } from './tabElectreIII.component';

describe('tabElectreIIIComponent', () => {
  let component: tabElectreIIIComponent;
  let fixture: ComponentFixture<tabElectreIIIComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ tabElectreIIIComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(tabElectreIIIComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
